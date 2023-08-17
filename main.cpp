//Created by Tony Aguilar
//08/13/2023

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

class ItemTracker {
private:
    std::map<std::string, int> itemFrequency; // A map to store item names and their frequencies

public:
    // Load data from a file and populate the itemFrequency map
    void load_data(const std::string& filename) {
        std::ifstream file(filename);
        if (file.is_open()) {
            std::string item;
            while (std::getline(file, item)) {
                // Increment the frequency for each item
                itemFrequency[item]++;
            }
            file.close();
        }
    }

    // Save the itemFrequency map to a file
    void save_data(const std::string& filename) {
        std::ofstream file(filename);
        if (file.is_open()) {
            for (const auto& pair : itemFrequency) {
                file << pair.first << " " << pair.second << "\n";
            }
            file.close();
        }
    }

    // Search for the frequency of a specific item (case-insensitive)
    int search_frequency(const std::string& item) {
        std::string lowercaseItem = item;
        std::transform(lowercaseItem.begin(), lowercaseItem.end(), lowercaseItem.begin(), ::tolower);

        int frequency = 0;
        for (const auto& pair : itemFrequency) {
            std::string lowercaseKey = pair.first;
            std::transform(lowercaseKey.begin(), lowercaseKey.end(), lowercaseKey.begin(), ::tolower);

            if (lowercaseKey == lowercaseItem) {
                frequency = pair.second;
                break;
            }
        }

        return frequency;
    }

    // Print the frequency list of items
    void print_frequency_list() {
        for (const auto& pair : itemFrequency) {
            std::cout << pair.first << " " << pair.second << "\n";
        }
    }

    // Print a histogram of items based on their frequency
    void print_histogram() {
        for (const auto& pair : itemFrequency) {
            std::cout << pair.first << " ";
            for (int i = 0; i < pair.second; ++i) {
                std::cout << "*";
            }
            std::cout << "\n";
        }
    }

    // Get a sorted frequency list of items (sorted by frequency)
    std::vector<std::pair<std::string, int>> get_sorted_frequency_list() const {
        std::vector<std::pair<std::string, int>> sortedList(itemFrequency.begin(), itemFrequency.end());
        std::sort(sortedList.begin(), sortedList.end(), [](const auto& a, const auto& b) {
            return a.second > b.second;
            });
        return sortedList;
    }
};

int main() {
    ItemTracker tracker;
    tracker.load_data("CS210_Project_Three_Input_File.txt");

    // Display a menu for user interaction
    while (true) {
        std::cout << "\nMenu:\n";
        std::cout << "1. Search for an item\n";
        std::cout << "2. Print frequency list\n";
        std::cout << "3. Print histogram\n";
        std::cout << "4. Exit\n";

        int choice;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        // Perform actions based on user's choice
        switch (choice) {
        case 1: {
            std::string item;
            std::cout << "Enter the item to search for: ";
            std::cin >> item;
            int frequency = tracker.search_frequency(item);
            std::cout << "The frequency of " << item << " is " << frequency << "\n";
            break;
        }
        case 2: {
            // Print the frequency list of items
            tracker.print_frequency_list();
            break;
        }
        case 3: {
            // Print a histogram of items based on their frequency
            tracker.print_histogram();
            break;
        }
        case 4:
            // Save data to a file and exit the program
            tracker.save_data("frequency.dat");
            std::cout << "Data saved to frequency.dat. Exiting...\n";
            return 0;
        default:
            std::cout << "Invalid choice. Please select a valid option.\n";
        }
    }

    return 0;
}
