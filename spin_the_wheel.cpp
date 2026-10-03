#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <chrono>
#include <thread>
#include <limits>

class UnpredictableWheel {
private:
    std::vector<std::string> options;
    std::mt19937_64 rng;

public:
    UnpredictableWheel(int totalNodes) {
        for (int i = 1; i <= totalNodes; ++i) {
            options.push_back(std::to_string(i));
        }

        std::random_device rd;
        std::seed_seq ss{
            rd(),
            static_cast<unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count()),
            static_cast<unsigned int>(reinterpret_cast<uintptr_t>(this)),
            rd()
        };
        rng.seed(ss);
    }

    std::string spin() {
        if (options.empty()) return "";
        std::uniform_int_distribution<size_t> dist(0, options.size() - 1);
        return options[dist(rng)];
    }
};

void dramaticDelay() {
    std::cout << "\nSpinning";
    std::cout.flush();
    for (int i = 0; i < 3; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(400));
        std::cout << ".";
        std::cout.flush();
    }
    std::cout << "\nSlowing down";
    std::cout.flush();
    for (int delay : {500, 900, 1400}) {
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        std::cout << ".";
        std::cout.flush();
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
    std::cout << "\n\n";
}

std::string getAnnouncement(const std::string& node) {
    std::vector<std::string> phrases = {
        "... The chosen one is " + node,
        "... Destiny points directly to " + node,
        "... The wheel settles on " + node,
        "... The universe selected " + node,
        "... Node " + node + " has emerged"
    };

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> dist(0, phrases.size() - 1);
    return phrases[dist(gen)];
}

int main() {
    int nodes = 0;
    std::cout << "Enter node count: ";
    std::cin >> nodes;

    UnpredictableWheel wheel(nodes);

    char choice = 'y';
    while (choice == 'y' || choice == 'Y') {
        dramaticDelay();
        std::cout << getAnnouncement(wheel.spin()) << "\n\n";

        std::cout << "Spin again? (y/n): ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    return 0;
}
