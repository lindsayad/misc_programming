extern "C" {
  void pstr(const char*);
};
int main(int argc, char** argv) {
    if (argc > 1) {
        pstr(argv[1]);
        } else {
        pstr("hello");
        }
    return 0;
    }
