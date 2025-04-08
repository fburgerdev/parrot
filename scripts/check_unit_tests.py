from pathlib import Path

# src_name
def src_name(src_name: str):
  if src_name == "main":
    return "main"
  return src_name[0:src_name.find('_test')]
# test_name
def test_name(src_name: str):
  return src_name + "_test"

# DirDiff
class DirDiff:
  # (constructor)
  def __init__(self):
    self.total_count = 0
    self.directories = []
    self.files = []

# exists
def exists(path: Path, suffixes: list[str]):
  for suffix in suffixes:
    if Path(str(path) + suffix).exists():
      return True
  return False
# remove_suffixes
def remove_suffixes(files: list[str]):
  result = set()
  for file in files:
    file = file[0:file.find('.')]
    if file.endswith("_impl"):
      file = file[0:file.find("_impl")]
    result.add(file)
  return result

# check_dir_diff
def check_dir_diff(src: Path, dest: Path, suffixes: list[str], name_transform):
  diff = DirDiff()
  for root_path, _, files in src.walk():
    rel_path = root_path.relative_to(src)
    if (dest / rel_path).exists():
      for file in remove_suffixes(files):
        if not exists(dest / rel_path / name_transform(file), suffixes):
          diff.files.append(rel_path / name_transform(file))
          diff.total_count += 1
    else:
      missing_file_count = 0
      for file in remove_suffixes(files):
        if not exists(dest / rel_path / name_transform(file), suffixes):
          missing_file_count += 1
          diff.total_count += 1
      diff.directories.append((rel_path, missing_file_count))
  return diff

# check_directories
def check_directories(src_dir: Path, tests_dir: Path, verbose: bool):
  # missing tests
  missing = check_dir_diff(src_dir, tests_dir, ['.cc'], test_name)
  if missing.total_count > 0:
    print(f"| There are missing test files {{ {missing.total_count} total }}:")
    for directory, directory_count in missing.directories:
      print(f"| - {directory} {{ {directory_count} units }}")
    for file in missing.files:
      print(f"| - {file}")
  # zombie tests
  zombie = check_dir_diff(tests_dir, src_dir, ['.hh', '.cc'], src_name)
  zombie.total_count -= 1
  zombie.files.remove(Path("main"))
  if zombie.total_count > 0:
    print(f"| There are zombie test files {{ = {zombie.total_count} total}}:")
    for directory, directory_count in zombie.directories:
      print(f"| - {directory} {{ {directory_count} files }}")
    for file in zombie.files:
      print(f"| - {file}")
  # success
  if missing.total_count == 0 and zombie.total_count == 0:
    return True
  else:
    return False

# check_unit_tests
def check_unit_tests(verbose: bool):
  # file_path
  file_path = Path(__file__).resolve()
  # repo_path
  repo_path = file_path.parents[1]
  # check
  print("Check unit-tests")
  success = check_directories(repo_path / "src", repo_path / "tests", verbose)
  if success:
    print("\u2713 Success")
  else:
    print("\u2717 Failure")
  return success

# __main__
if __name__ == '__main__':
  if check_unit_tests(True):
    print()
    print("Everything is fine.")
  else:
    print()
    print("** Found errors **")