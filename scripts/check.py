from check_unit_tests import check_unit_tests
from check_line_length import check_line_length
from check_examples import check_examples

# __main__
if __name__ == '__main__':
  # verbose
  verbose = False
  # checks
  success = True
  success &= check_unit_tests(verbose)
  print()
  success &= check_line_length(verbose)
  print()
  success &= check_examples(verbose)
  print()
  # conclusion
  if success:
    print("Everything is fine.")
  else:
    print("** Found errors **")