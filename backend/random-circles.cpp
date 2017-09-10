#include <is/is.hpp>
#include <is/packer.hpp>
#include <random>
#include <chrono>

int main(int , char **) {
  auto is = is::connect("amqp://localhost:5672");

  std::default_random_engine generator;
  std::uniform_real_distribution<double> distribution(0.0, 1.0);

  for (;;) {
    is.publish("circles", is::msgpack(std::make_tuple(
                              distribution(generator), distribution(generator),
                              distribution(generator))));
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
}