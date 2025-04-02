from pathlib import Path

def compare_directories(dir1: Path, dir2: Path, common: Path, verbose: bool):
  file_map = dict()
  dir1_rel = dir1.relative_to(common)
  dir2_rel = dir2.relative_to(common)
  dir1_count = 0
  dir2_count = 0
  for root, _, files in dir1.walk():
    root_rel = root.relative_to(dir1)
    for file in files:
      key = (root_rel / file, (root / file).stat().st_mtime)
      if key in file_map:
        file_map[key].append("dir1")
      else:
        file_map[key] = ["dir1"]
      dir1_count += 1
  for root, _, files in dir2.walk():
    root_rel = root.relative_to(dir2)
    for file in files:
      key = (root_rel / file, (root / file).stat().st_mtime)
      if key in file_map:
        file_map[key].append("dir2")
      else:
        file_map[key] = ["dir2"]
      dir2_count += 1
  if dir1_count == dir2_count == len(file_map):
    if verbose:
      print(f"| Directory {dir1_rel} and Directory {dir2_rel} are the same.")
    return True
  else:
    print(f"| Directory {dir1_rel} and Directory {dir2_rel} are not the same:")
    for (path, mtime), dirs in file_map.items():
      if "dir1" not in dirs:
        print(f"| - dir {dir1_rel} does not contain {path} (mtime = {mtime})")
      if "dir2" not in dirs:
        print(f"| - dir {dir2_rel} does not contain {path} (mtime = {mtime})")
    return False

# check_examples
def check_examples(verbose: bool):
  # file_path
  file_path = Path(__file__).resolve()
  # repo_path
  repo_path = file_path.parents[1]
  # check
  success = True
  examples = list()
  print("Check examples")
  for example in (repo_path / "examples").iterdir():
    if len(examples) > 0:
      success &= compare_directories(examples[-1] / ".parrot", example / ".parrot", repo_path / "examples", verbose)
    examples.append(example)
  if success:
    print("\u2713 Success")
  else:
    print("\u2717 Failure")
  return success

# __main__
if __name__ == '__main__':
  if check_examples(True):
    print()
    print("Everything is fine.")
  else:
    print()
    print("** Found errors **")