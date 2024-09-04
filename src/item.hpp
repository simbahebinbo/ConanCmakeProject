#ifndef ITEM_HPP
#define ITEM_HPP

#include <iostream> // Include for output

class Item {
public:
  // Constructor with three arguments to initialize member variables
  Item(const std::string& name, double price, const std::string& description)
    : name(name), price(price), description(description) {}

  // Function to print item details (const indicates no modification)
  void printItem() const {
    std::cout << "Name: " << name << std::endl;
    std::cout << "Price: $" << price << std::endl;
    std::cout << "Description: " << description << std::endl;
  }

private:
  // Member variables to store item information
  std::string name;
  double price;
  std::string description;
};

#endif
