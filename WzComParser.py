import os
from pathlib import Path

def ParseAnimation(dir_path: str):
    """
    dir_path에 있는 형태가 "<숫자>_<숫자>.png"인 파일을 찾아,
    정렬 후 0.png, 1.png, 2.png 식으로 순차 리네이밍한다.
    """

    directory = Path(dir_path)
    if not directory.is_dir():
        print(f"에러: '{dir_path}'는 올바른 디렉터리 경로가 아닙니다.")
        return

    # 디렉터리 내에서 .png 파일 중, 파일명에 '_'가 포함된 것만 필터링
    files = [
        f for f in directory.iterdir()
        if f.is_file() and f.suffix.lower() == ".png" and "_" in f.stem
    ]

    # 파일명에서 첫 번째 숫자 추출 → 그 숫자를 기준으로 정렬
    # 예) "0_90.png" → stem = "0_90" → split("_")[0] = "0" → int("0")
    #      "90_180.png" → stem = "90_180" → split("_")[0] = "90" → int("90")
    files = sorted(files, key=lambda x: int(x.stem.split('_')[0]))

    # 순차적으로 0.png, 1.png, 2.png ... 로 이름 변경
    for index, file_path in enumerate(files):
        new_name = directory / f"{index}.png"
        # 이미 0.png, 1.png 등이 있을 경우 덮어쓰기를 할 수 있으니 주의
        file_path.rename(new_name)

    print("리네이밍 완료!")









if __name__ == "__main__":
    print("디렉터리를 복사해서 입력해주세요 : ")
    while True:
        inp = input()
        ParseAnimation(inp)