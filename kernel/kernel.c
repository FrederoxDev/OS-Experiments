void main() {
    char* video_memory = (char*)0xb8000;
    *video_memory = 'Z';

    video_memory++;
    video_memory++;
    *video_memory = 'Z';
}