import os

def replace_tabs_with_spaces(directory, num_spaces=2):
  for root, _, files in os.walk(directory):
    for file in files:
      file_path = os.path.join(root, file)
      if not file_path.endswith(".cc") and not file_path.endswith(".hh") and not file_path.endswith(".json"):
        continue
      try:
        with open(file_path, 'r', encoding='utf-8') as f:
          content = f.read()

          updated_content = content.replace('\t', ' ' * num_spaces)
            
          with open(file_path, 'w', encoding='utf-8') as f:
            f.write(updated_content)
            
          print(f"Processed: {file_path}")
      except Exception as e:
        print(f"Skipping {file_path}: {e}")

def check_long_lines(directory, max_length=80):
  """
  Recursively checks all files for lines exceeding max_length and outputs the files with those lines.
  
  :param directory: The root directory to scan for files.
  :param max_length: The maximum allowed line length.
  """
  for root, _, files in os.walk(directory):
    for file in files:
      file_path = os.path.join(root, file)
      if not file_path.endswith(".cc") and not file_path.endswith(".hh") and not file_path.endswith(".json"):
        continue
      try:
        with open(file_path, 'r', encoding='utf-8') as f:
          lines = f.readlines()
        
        found = False
        for i, line in enumerate(lines, start=1):
          if len(line) > max_length:
            print(f"{file_path}, Line {i}: {line.strip()}")
            found = True
        if found:
          print()
      except Exception as e:
        print(f"Skipping {file_path}: {e}")

if __name__ == "__main__":
  directory = input("Enter the directory path: ").strip()
  replace_tabs_with_spaces(directory)
  check_long_lines(directory)