import unittest
import thing_to_test

class TestMyModule(unittest.TestCase):

    def setUp(self):
        print("setUp")

    def tearDown(self):
        print("tearDown")

    def test_incorrect_type(self):
        def try_incorrect_type():
            thing_to_test.is_even(3.1415)

        self.assertRaises(TypeError, try_incorrect_type)
        # self.assertRaises(ValueError, try_incorrect_type) # this assert will fail

    def test_some_values(self):

        self.assertTrue(thing_to_test.is_even(8))
        # self.assertFalse(thing_to_test.is_even(9))


if __name__ == "__main__":
    unittest.main()

