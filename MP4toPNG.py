from moviepy.editor import VideoFileClip
import os
from PIL import Image


def extract_frames_moviepy(video_path, output_dir):
    if not os.path.exists(output_dir):
        os.makedirs(output_dir)

    clip = VideoFileClip(video_path, )
    frame_idx = 0
    for frame in clip.iter_frames():
        img = Image.fromarray(frame)
        img.save(os.path.join(output_dir, f"frame_{frame_idx:06d}.png"))
        frame_idx += 1

    print(f"총 {frame_idx} 프레임을 추출했습니다.")


extract_frames_moviepy(r"E:\Videos\1.mp4", r"E:\Videos")