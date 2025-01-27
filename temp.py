from pathlib import Path
import re

def rename_frames_in_range(directory, start_num=19, end_num=281):
    pattern = re.compile(r"^frame_0*(\d+)\.png$")
    dir_path = Path(directory)
    for file_path in sorted(dir_path.iterdir()):
        match = pattern.match(file_path.name)
        if not match:
            continue
        frame_num = int(match.group(1))
        if start_num <= frame_num <= end_num:
            new_index = frame_num - (start_num - 1)
            new_name = f"{new_index}.png"
            file_path.rename(dir_path / new_name)
            print(f"Renamed {file_path.name} -> {new_name}")



rename_frames_in_range(r"F:\CppProject\MapleStory\Resources\Textures\Intro\Lucid")