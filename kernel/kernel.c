void some_function() {
    return;
}

void main() {
    char* video_memory = (char*)0xb8000;
    *video_memory = 'Z';

    some_function();
}