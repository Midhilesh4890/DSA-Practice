"""Assign as many qualified volunteers to questions as possible.

Question:
    A question and volunteer are compatible when their tag sets intersect.
    Each question and volunteer may appear in at most one assignment. Return a
    maximum-cardinality mapping from question ID to volunteer name (or ID when
    no display name is supplied).

Approach:
    Build the bipartite compatibility graph. For each question, a DFS searches
    for an augmenting path, reassigning earlier matches when necessary.

Complexity:
    Graph construction is O(Q*V*T); matching is O(Q*E), where E is the number
    of compatible pairs and T is tag-intersection cost. Space is O(Q+V+E).
"""


def find_maximum_matching(questions, volunteers):
    """Return ``{question_id: volunteer_name_or_id}`` for a maximum matching."""
    question_ids = [question["id"] for question in questions]
    volunteer_by_id = {volunteer["id"]: volunteer for volunteer in volunteers}
    if len(set(question_ids)) != len(question_ids):
        raise ValueError("question IDs must be unique")
    if len(volunteer_by_id) != len(volunteers):
        raise ValueError("volunteer IDs must be unique")

    graph = {}
    for question in questions:
        question_tags = set(question.get("tags", ()))
        graph[question["id"]] = [
            volunteer["id"]
            for volunteer in volunteers
            if question_tags.intersection(volunteer.get("tags", ()))
        ]

    volunteer_to_question = {}

    def augment(question_id, visited):
        for volunteer_id in graph[question_id]:
            if volunteer_id in visited:
                continue
            visited.add(volunteer_id)
            previous_question = volunteer_to_question.get(volunteer_id)
            if previous_question is None or augment(previous_question, visited):
                volunteer_to_question[volunteer_id] = question_id
                return True
        return False

    for question_id in question_ids:
        augment(question_id, set())

    assignments = {}
    for volunteer_id, question_id in volunteer_to_question.items():
        volunteer = volunteer_by_id[volunteer_id]
        assignments[question_id] = volunteer.get("name", volunteer_id)
    return assignments


def _run_tests():
    questions = [
        {"id": "q1", "tags": ["python"]},
        {"id": "q2", "tags": ["python", "java"]},
    ]
    volunteers = [
        {"id": "v1", "name": "Ada", "tags": ["python"]},
        {"id": "v2", "name": "Grace", "tags": ["java"]},
    ]
    assignments = find_maximum_matching(questions, volunteers)
    assert assignments == {"q1": "Ada", "q2": "Grace"}
    assert find_maximum_matching([{"id": 1, "tags": ["x"]}], [{"id": 2, "tags": ["x"]}]) == {1: 2}


if __name__ == "__main__":
    _run_tests()
    print("All tests passed.")
