#include <javilo/spsc_queue.h>

int main(int argc, char** argv)
{
  (void)argc, (void)argv;

  using namespace javilo;
  spsc_queue<int> queue{1024};

  return 0;
}
