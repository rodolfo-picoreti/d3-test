#include <chrono>
#include <cmath>
#include <is/is.hpp>
#include <is/packer.hpp>
#include <random>

int main(int, char **) {
  auto is = is::connect("amqp://localhost:5672");

  std::default_random_engine generator;
  std::uniform_real_distribution<double> distribution(0.0, 1.0);

  for (int i = 0;; ++i) {
    const double w = 0.1;
    is.publish("circles",
               is::msgpack(std::make_tuple(std::cos(i * w), std::sin(i * 2 * w),
                                           distribution(generator))));
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}