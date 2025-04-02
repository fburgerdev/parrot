from pathlib import Path

# check_repo
def check_repo(repo_path: Path, ignore_paths: list[Path], verbose: bool):
  count = 0
  for root, _, file_names in repo_path.walk():
    for ignore_path in ignore_paths:
      if root.is_relative_to(ignore_path):
        break
    else:
      for file_name in file_names:
        for suffix in [ ".txt", ".hh", ".cc", ".py", ".json", ".yaml" ]:
          if file_name.endswith(suffix):
            with open(root / file_name, encoding='utf-8') as file:
              to_long_lines = []
              lines = [ line[:-1] if len(line) > 0 else line for line in file.readlines() ]
              for i in range(len(lines)):
                if len(lines[i]) > 80:
                  to_long_lines.append(i)
              if len(to_long_lines) > 0:
                if verbose:
                  print(f"| Found in {(root / file_name).relative_to(repo_path)}:")
                  for line_index in to_long_lines:
                    print(f"| {lines[line_index]} [length {len(lines[line_index])} in line {line_index}]")
                  print("|")
                else:
                  print(f"| - {(root / file_name).relative_to(repo_path)} {{ {len(to_long_lines)} lines }}")
              count += len(to_long_lines)
  print(f"| Found {count} lines with more than 80 characters.")
  return count == 0

# check_line_length
def check_line_length(verbose: bool):
  # file_path
  file_path = Path(__file__).resolve()
  # repo_path
  repo_path = file_path.parents[1]
  # check
  print("Check line length")
  ignore_paths = [
    repo_path / ".git", repo_path / ".vs", 
    repo_path / "build", repo_path / "out",
    repo_path / "vendor"
  ]
  success = check_repo(repo_path, ignore_paths, verbose)
  if success:
    print("\u2713 Success")
  else:
    print("\u2717 Failure")
  return success

# __main__
if __name__ == '__main__':
  if check_line_length(True):
    print()
    print("Everything is fine.")
  else:
    print()
    print("** Found errors **")