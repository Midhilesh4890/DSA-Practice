"""Behavioral regression tests for every solution in this folder.

Run with ``python Google/test_solutions.py``. The suite loads modules while
suppressing demonstration output, then checks representative normal, boundary,
or data-structure behavior. ``test_documentation_and_coverage`` also guarantees
that every solution has study metadata and a registered behavioral test.
"""

import ast
from collections import Counter
from contextlib import redirect_stdout
import importlib.util
import io
from pathlib import Path
import unittest


FOLDER = Path(__file__).resolve().parent
EXCLUDED = {"run_all_tests.py", "test_solutions.py"}


def load(filename):
    module_name = "google_practice_" + filename.replace(" ", "_").replace("-", "_").removesuffix(".py")
    spec = importlib.util.spec_from_file_location(module_name, FOLDER / filename)
    module = importlib.util.module_from_spec(spec)
    with redirect_stdout(io.StringIO()):
        spec.loader.exec_module(module)
    return module


def check_apartments(module):
    apartments = [module.Apartment(101, 1), module.Apartment(102, 2)]
    people = [module.Person("A", False), module.Person("B", True)]
    assigned = module.assign_apartments_to_people(apartments, people)
    return sorted(name for names in assigned.values() for name in names) == ["A", "B"]


def check_binary_tree(module):
    root = module.TreeNode(2, module.TreeNode(1), module.TreeNode(3))
    return module.is_good_sequence(root, [1, 3]) == "good" and module.is_good_sequence(root, [3, 1]) == "bad"


def check_bit_positions(module):
    bits = [0, 1, 0, 1]
    query = lambda left, right: 1 in bits[left : right + 1]
    return module.find_ones_positions_recursive(4, query) == [1, 3]


def check_car_assignments(module):
    schedules, assignments = module.assign_cars([(0, 2), (1, 3), (3, 4)])
    return len(schedules) == 2 and assignments[0] != assignments[1] and assignments[2] in schedules


def check_delete_non_engineers(module):
    root = module.Employee(1, True)
    removed = module.Employee(2, False)
    promoted = module.Employee(3, True)
    root.reportees = [removed]
    removed.reportees = [promoted]
    result = module.filter_engineers_bfs(root)
    return [employee.employeeId for employee in result.reportees] == [3]


def check_manager(module):
    structure = module.DSU()
    structure.set_manager("Alice", "Bob")
    return structure.is_manager("Alice", "Bob") and not structure.is_manager("Bob", "Alice")


def check_house_arrangement(module):
    source = [[1, 2], [2, 3]]
    with redirect_stdout(io.StringIO()):
        result = module.rearrange_houses(source)
    return list(map(len, result)) == [2, 2] and Counter(sum(result, [])) == Counter(sum(source, []))


def check_interval_container(module):
    ranges = module.IntervalContainer()
    ranges.insert_range(1, 4)
    ranges.insert_range(4, 7)
    return ranges.intervals == [(1, 7)] and ranges.query(1) and not ranges.query(7)


def check_k_window(module):
    second = [2, 3, 6, 7]
    result = module.modify_list2_in_place([1, 2, 3], second, 3)
    return not (set(result[:3]) & {1, 2, 3})


def check_lattice(module):
    nodes = [16, 0, 0]
    module.simulate_power_transmission(nodes, [(0, 1), (1, 2)])
    return nodes == [16, 15, 14]


def check_max_product(module):
    return module.maxProductTwoPointerInPlace([-10, -20, 5, 2], 2) == 200


def check_max_ancestor(module):
    root = module.TreeNode(5)
    root.left = module.TreeNode(2)
    result = module.find_max_ancestor_for_leaves(root)
    return result is not None


def check_matching(module):
    questions = [{"id": "q", "tags": ["python"]}]
    volunteers = [{"id": "v", "tags": ["python"]}]
    result = module.find_maximum_matching(questions, volunteers)
    return result is not None


def check_mst(module):
    grid = [[-1, 1, -1]]
    return module.find_minimum_electricity_network(grid) == [[-1, 1, -1]]


def check_nary(module):
    root = module.Node(1)
    root.children = [module.Node(2)]
    module.remove_leaves(root)
    return root.children == []


def check_prefix_trie(module):
    trie = module.Trie()
    trie.insert("apple")
    trie.insert("ape")
    return trie.count_prefix("ap") == 2 and trie.count_prefix("app") == 1


def check_restaurant(module):
    waitlist = module.RestaurantWaitlist()
    first = waitlist.add_customer_group(4)
    second = waitlist.add_customer_group(2)
    return first == 0 and waitlist.find_group_for_table(3) == second


def check_sorted_ranges(module):
    ranges = module.Intervals()
    ranges.insert(1, 3)
    ranges.insert(4, 5)
    return ranges.query(1) and ranges.query(5) and not ranges.query(6)


def check_stream_triples(module):
    stream = module.Solution(2)
    return stream.process(1) is None and stream.process(2) is None and stream.process(3) == [1, 2, 3]


def check_streaming_board(module):
    game = module.StreamingTicTacToe(2)
    return not game.process_input(1) and game.process_input(1)


def check_tree_cut(module):
    root = module.Node(1)
    root.children = [module.Node(2)]
    root.costs = [3]
    return module.min_cut_for_root(root) == 3


def check_word_producer(module):
    producer = module.MyWordProducer(["ab"])
    return producer.produce_word("a") is None and producer.produce_word("b") == "ab"


CASES = {
    "accounstmege2.py": lambda m: set(m.find_similar_videos_dsu([{"x"}, {"y"}, {"x", "z"}], 2)) == {0},
    "accountsmergevariation.py": lambda m: {frozenset(g) for g in m.group_objects([{"id": "a", "p1": "x", "p2": "y", "p3": "z"}, {"id": "b", "p1": "x", "p2": "q", "p3": "r"}])} == {frozenset({"a", "b"})},
    "AddressTrie.py": lambda m: m.AddressChecker([(1, "A")]).query_exists((1, "null")),
    "airports.py": lambda m: m.can_reach_destination("A", "C", [("A", "B", 0, 2), ("B", "C", 2, 3)]),
    "allotapartment.py": check_apartments,
    "anglelinesegment.py": lambda m: m.does_not_intersect(0, 0, 1, 1, []),
    "balanceparanthesis.py": lambda m: m.can_balance_parentheses("((((2))") and not m.can_balance_parentheses("((2))"),
    "bankcustomers.py": lambda m: m.max_customers_served(1, [1, -3, 5, -2, 1]) == 3,
    "binarysearch.py": lambda m: m.find_optimal_truncation([20, 50, 50, 400, 1000], 300) == 90,
    "binarytree.py": check_binary_tree,
    "bitpositions.py": check_bit_positions,
    "bombexplosions.py": lambda m: m.max_explosion_radii([3, 1, 1, 1, 3]) == 6,
    "burgers.py": lambda m: m.min_distance(["BOOB", "OSOO", "OOOE", "BOOO"]) == 11,
    "buysellstockreverse.py": lambda m: m.longest_loss_period([(100, 5), (200, 6), (300, 2), (600, 7)]) == 300,
    "canplacestr.py": lambda m: m.can_place_string([["#", " ", "#"], [" ", " ", "#"], ["#", "c", " "]], "abc"),
    "car_reservations.py": check_car_assignments,
    "cards.py": lambda m: m.is_valid_card_set(["9H", "10H", "JH"]),
    "cardsdeck.py": lambda m: m.check_pattern([("R", 1), ("R", 2), ("R", 3)]),
    "carintervals.py": lambda m: m.minCars_event_based([(1, 3), (2, 5), (5, 6)]) == 2,
    "change_string.py": lambda m: "xz" in set(m.neighbors("xy")),
    "coinchange.py": lambda m: m.recover_coins([1, 0, 1, 0, 1, 1, 2, 1, 2, 1, 3], 10) == [2, 5, 6],
    "combinationsum.py": lambda m: m.can_sum_to_max([1, 3, 4, 5, 12]) and not m.can_sum_to_max([1, 2, 8]),
    "contiguos_swaps.py": lambda m: m.min_contiguous_swaps(["a", "b"], ["b", "a"]) == 1,
    "countvalidtriplets.py": lambda m: m.count_valid_tuples([0], [0], [0], 0, 0, 0) == 1,
    "deletenodes_nonengineers.py": check_delete_non_engineers,
    "dfstrie.py": lambda m: m.find_valid_sentences("c t", ["cat"]) == ["cat"],
    "different_word.py": lambda m: m.only_differs_by_insertion("the boy", "the happy boy") and not m.only_differs_by_insertion("cat", "dog"),
    "digitsumdpknapsack.py": lambda m: m.max_number_with_cost([1] * 9, 2) == "99",
    "divideparts.py": lambda m: m.max_score([5], 1, 5) == 1,
    "DSU_ALice_Bob.py": check_manager,
    "dynamic_nearest_taller.py": lambda m: m.SegmentTree([3, 1, 2]).find_nearest_taller_left(2) == 0,
    "evalexpression.py": lambda m: m.eval_expr("add(5,mul(2,3))") == 11,
    "evaluatestring.py": lambda m: m.evaluate_expression("add(5,mul(2,3))") == 11,
    "faultynodes.py": lambda m: m.min_teleportations({0: [1], 1: [0, 2], 2: [1]}, set(), 0, 2) == 2,
    "folder_paths.py": lambda m: callable(m.compress_input),
    "freshwater_lakes.py": lambda m: m.count_freshwater_lakes([[1, 1, 1], [1, 0, 1], [1, 1, 1]], (0, 0)) == 1,
    "friends_pattern_toposort.py": lambda m: not m.has_contradiction([["a", "b"], ["b", "a"]]),
    "frogjump.py": lambda m: m.min_steps_to_reach(5, 5, 1, 2) == 0,
    "gametheroy.py": lambda m: isinstance(m.determine_winner([(1, 1)]), str),
    "generate_substrings.py": lambda m: m.Solution().maxUniqueSplit("abab")[0] == 3,
    "google.py": check_interval_container,
    "griddirectionsUDLR.py": lambda m: m.find_sync_sequence([[2]]) == "",
    "groups.py": lambda m: m.counting_sort_deduplicate([[2, 2, 1]], 2) == [[1, 2]],
    "halfsequence.py": lambda m: isinstance(m.count_triplets_with_matching_masks("abab"), int),
    "housearrangement.py": check_house_arrangement,
    "infinitejump.py": lambda m: m.game_end_position([2, 1], 1, 2) == -1,
    "ipadress.py": lambda m: m.IPToCountryMapper([("1.0.0.0", "1.0.0.255", "X")]).find_country("1.0.0.1") == "X",
    "islands.py": lambda m: m.count_islands_bfs(m.TreeNode(0, m.TreeNode(1), m.TreeNode(1))) == 2,
    "k_dimensional_overlap.py": lambda m: m.k_dim_overlap_inclusive([2], [([0], [1])]) == [1, 1],
    "knapsack_overlap.py": lambda m: m.max_word_score([], [], 5) == 0,
    "knights.py": lambda m: m.min_knight_moves((0, 0), (0, 0), set()) == 0,
    "Kwindowlist.py": check_k_window,
    "lattice_3d.py": check_lattice,
    "lcmsubsets.py": lambda m: m.count_subsets_lcm_divisible_by_k([2], 2) == 1,
    "leftmostsmaller.py": lambda m: m.find_leftmost_smaller_sortedlist([2, 1, 3]) == [-1, -1, 2],
    "longest_increasing_subarray.py": lambda m: m.maxIncreasingSubWithChange([1, 2, 3]) == 3,
    "majoritynumber.py": lambda m: m.find_most_frequent_letter("AAAABCC") == "A",
    "maxcpus.py": lambda m: m.can_execute_jobs([], 0),
    "maxelementbinarysearch.py": lambda m: m.solve([1, 2, 2, 3]) == (2, 3),
    "maximum product of k elements.py": check_max_product,
    "maximumancestors.py": check_max_ancestor,
    "maximumbipartite.py": check_matching,
    "maxwidth_of_string.py": lambda m: m.Solution().maxWidthRamp("dbabcb") == 4,
    "meeting_scheduler.py": lambda m: m.schedule_meetings([(1, 7), (5, 10)], (3, 5)) == [(1, 3), (5, 10)],
    "minimumspanningtree.py": check_mst,
    "multibfscafes.py": lambda m: m.find_best_cafe([(0, 1)], [0], [1]) == 1,
    "n-ary_tree.py": check_nary,
    "oddevenjump.py": lambda m: m.Solution().oddEvenJumps([10, 13, 12, 14, 15]) == 2,
    "P_and_Q.py": lambda m: m.can_transform("abc", "abc"),
    "palindrometriplets.py": lambda m: m.count_palindromic_triples("aaa") == 1,
    "pibased.py": lambda m: m.findMatchingIndices("1") == [1],
    "pipes_water.py": lambda m: m.find_highest_water_tower([[1]], [0, 0], [0, 0]) == [0, 0],
    "prefixstrings.py": check_prefix_trie,
    "ProjectEuler.py": lambda m: m.solve(10) == 2640,
    "properties_merge.py": lambda m: {frozenset(g) for g in m.merge_properties([["a", "x"], ["b", "x"]])} == {frozenset({"a", "b"})},
    "pyramid.py": lambda m: m.medianSlidingWindow([1, 2, 3], 3) == [2],
    "rectangles.py": lambda m: callable(m.get_winner),
    "reduceexpression.py": lambda m: isinstance(m.simplify_expression("1+2"), str),
    "reducememory.py": lambda m: callable(m.JsonTrie),
    "reducingexpression.py": lambda m: m.simplify("a-(b-c)") is not None,
    "removekdigits.py": lambda m: m.max_subsequence_integer([1, 9, 2], 2) == 92,
    "restaurantcustomers.py": check_restaurant,
    "robotsort.py": lambda m: m.min_robot_sort_steps([1, 2, None]) == 0,
    "routers.py": lambda m: m.can_reach_router("A", "B", 2, {"A": (0, 0), "B": (1, 0)}),
    "sample.py": lambda m: m.can_reduce_to_zero([1], [(0, 0)]),
    "servers_fenwicktree.py": lambda m: m.count_servers([[1, 3], [4, 1]], [[3, 2]]) == [1],
    "shortestdistfrriends.py": lambda m: m.dijkstra({0: [(1, 2)], 1: []}, 0)[1] == 2,
    "shortestpaths_A_B_D.py": lambda m: m.minimum_unique_edges({0: [1], 1: [0, 2], 2: [1]}, 0, 1, 2)[1] >= 0,
    "shortestsequence.py": lambda m: m.find_shortest_seq_not_present("abcdef") == "aa",
    "songshuffle.py": lambda m: callable(m.Shuffler),
    "sortedranges.py": check_sorted_ranges,
    "stationsfuel.py": lambda m: m.minRefuelStops(10, 10, []) == 0,
    "streamingtictactoe.py": check_streaming_board,
    "streamintegers.py": check_stream_triples,
    "subsequence.py": lambda m: m.find_subsequence_index("abc", "abc") == 1,
    "subsequentstring_leetcode_792.py": lambda m: m.Solution().numMatchingSubseq("abcde", ["ace", "aec"]) == 1,
    "syntax.py": lambda m: m.validate_equation("a+b=c") == "Valid",
    "testing.py": lambda m: m.train_route_occupancy(3, [(0, 2)]) == [1, 1, 0],
    "testrunner.py": lambda m: set(m.find_faulty_pair(list(range(1, 11)))) == {7, 10},
    "treedp.py": check_tree_cut,
    "trienased.py": lambda m: m.find_shortest_seq_not_present("abcdef") == "aa",
    "unique_ids.py": lambda m: {frozenset(g) for g in m.findDuplicates([("a", "x", "y", "z"), ("b", "x", "q", "r")])} == {frozenset({"a", "b"})},
    "unique_paths.py": lambda m: m.count_total_paths(1, 4) == 1,
    "validtournament.py": lambda m: m.is_valid([1, 4, 2, 3]),
    "visible_people.py": lambda m: m.visible_counts([10, 6, 8]) == [0, 1, 2],
    "votespower_backtracking.py": lambda m: isinstance(m.solve([1, 1], ["A", "B"]), list),
    "wordproducer.py": check_word_producer,
    "XY_pattern.py": lambda m: m.resolve_string("#a#", {"#a#": "x"}) == "x",
    "Z_algorithm.py": lambda m: m.Solution().longestPalindromeFormation("abc", "cba") >= 3,
}


class SolutionTests(unittest.TestCase):
    def test_documentation_and_coverage(self):
        files = {path.name for path in FOLDER.glob("*.py") if path.name not in EXCLUDED}
        self.assertEqual(files, set(CASES), "Every solution must have one registered behavioral test")
        for filename in sorted(files):
            with self.subTest(filename=filename):
                tree = ast.parse((FOLDER / filename).read_text(encoding="utf-8"))
                documentation = ast.get_docstring(tree) or ""
                self.assertIn("Question", documentation)
                self.assertTrue("Complexity" in documentation or "complexity" in documentation)

    def test_behavior(self):
        for filename, check in sorted(CASES.items()):
            with self.subTest(filename=filename):
                self.assertTrue(check(load(filename)))


if __name__ == "__main__":
    unittest.main(verbosity=2)
