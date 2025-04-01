from check_unit_tests import check_unit_tests
from check_examples import check_examples

# __main__
if __name__ == '__main__':
  # checks
  success = True
  success &= check_unit_tests()
  print()
  success &= check_examples()
  print()
  # conclusion
  if success:
    print("Everything is fine.")
  else:
    print("** Found errors **")