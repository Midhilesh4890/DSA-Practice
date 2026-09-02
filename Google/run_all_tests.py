"""Compile and execute every standalone solution in the Google folder.

Run with ``python Google/run_all_tests.py`` from the repository root. Each
solution gets an isolated interpreter and a timeout, so accidental global state
or a hanging example cannot hide failures in later files.
"""

from pathlib import Path
import py_compile
import subprocess
import sys


TIMEOUT_SECONDS = 10
EXCLUDED = {"run_all_tests.py", "test_solutions.py"}


def run_all_tests():
    folder = Path(__file__).resolve().parent
    files = sorted(path for path in folder.glob("*.py") if path.name not in EXCLUDED)
    failures = []

    for path in files:
        try:
            py_compile.compile(str(path), doraise=True)
            completed = subprocess.run(
                [sys.executable, str(path)],
                cwd=folder.parent,
                capture_output=True,
                text=True,
                timeout=TIMEOUT_SECONDS,
                check=False,
            )
        except (py_compile.PyCompileError, subprocess.TimeoutExpired) as error:
            failures.append((path.name, str(error)))
            print(f"FAIL  {path.name}: {error}")
            continue

        if completed.returncode:
            detail = completed.stderr.strip().splitlines()
            message = detail[-1] if detail else f"exit code {completed.returncode}"
            failures.append((path.name, message))
            print(f"FAIL  {path.name}: {message}")
        else:
            print(f"PASS  {path.name}")

    print(f"\n{len(files) - len(failures)}/{len(files)} solution files passed.")
    return failures


if __name__ == "__main__":
    problems = run_all_tests()
    raise SystemExit(1 if problems else 0)
