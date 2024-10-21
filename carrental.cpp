#include <iostream>
#include <string>
#include <vector>
#include <ctime>
using namespace std;

class Car {
public:
    string carModel;
    string carNumber;
    float pricePerDay;
    bool isAvailable;

    Car(string model, string number, float price) {
        carModel = model;
        carNumber = number;
        pricePerDay = price;
        isAvailable = true;
    }

    void displayDetails() {
        cout << "Car Model: " << carModel << endl;
        cout << "Car Number: " << carNumber << endl;
        cout << "Price per Day: $" << pricePerDay << endl;
        cout << "Availability: " << (isAvailable ? "Available" : "Not Available") << endl;
    }
};

class Customer {
public:
    string name;
    string contactInfo;

    Customer(string n, string c) : name(n), contactInfo(c) {}

    void displayCustomerInfo() {
        cout << "Customer Name: " << name << endl;
        cout << "Contact Info: " << contactInfo << endl;
    }
};

class RentalRecord {
public:
    Customer customer;
    Car car;
    int rentalDays;
    time_t rentDate;
    bool isReturned;
    float totalCost;

    RentalRecord(Customer cust, Car cr, int days, time_t rentD)
        : customer(cust), car(cr), rentalDays(days), rentDate(rentD), isReturned(false), totalCost(0) {}

    void displayRecord() {
        cout << "Customer Name: " << customer.name << endl;
        cout << "Car Model: " << car.carModel << endl;
        cout << "Rental Days: " << rentalDays << endl;
        cout << "Rental Date: " << ctime(&rentDate);
        cout << "Returned: " << (isReturned ? "Yes" : "No") << endl;
        if (isReturned) {
            cout << "Total Cost: $" << totalCost << endl;
        }
        cout << "---------------------------\n";
    }
};

class RentalSystem {
private:
    vector<Car> cars;
    vector<RentalRecord> rentalHistory;

public:
    void addCar(const Car& car) {
        cars.push_back(car);
    }

    void displayAvailableCars() {
        cout << "Available Cars:\n";
        for (size_t i = 0; i < cars.size(); i++) {
            if (cars[i].isAvailable) {
                cout << i + 1 << ". ";
                cars[i].displayDetails();
                cout << endl;
            }
        }
    }

    void rentCar(int carIndex, int days, Customer customer) {
        if (carIndex < 1 || carIndex > cars.size() || !cars[carIndex - 1].isAvailable) {
            cout << "Invalid car selection or car is not available.\n";
        } else {
            cars[carIndex - 1].isAvailable = false;
            time_t now = time(0);  // Rental start time

            RentalRecord newRecord(customer, cars[carIndex - 1], days, now);
            rentalHistory.push_back(newRecord);

            cout << "You have rented the " << cars[carIndex - 1].carModel << " for " << days << " day(s).\n";
        }
    }

    void returnCar(int recordIndex) {
        if (recordIndex < 1 || recordIndex > rentalHistory.size() || rentalHistory[recordIndex - 1].isReturned) {
            cout << "Invalid rental record or car has already been returned.\n";
        } else {
            RentalRecord& record = rentalHistory[recordIndex - 1];
            time_t returnTime = time(0);
            double seconds = difftime(returnTime, record.rentDate);
            int actualDays = max(1, static_cast<int>(seconds / (60 * 60 * 24))); // Calculate rental period

            record.totalCost = actualDays * record.car.pricePerDay;
            record.isReturned = true;
            record.car.isAvailable = true;

            cout << "Car returned successfully.\n";
            cout << "Total cost for " << actualDays << " day(s): $" << record.totalCost << endl;
        }
    }

    void displayRentalHistory() {
        cout << "Rental History:\n";
        for (size_t i = 0; i < rentalHistory.size(); i++) {
            cout << i + 1 << ". ";
            rentalHistory[i].displayRecord();
        }
    }
};

int main() {
    RentalSystem rentalSystem;

    // Adding some cars to the system
    rentalSystem.addCar(Car("Toyota Corolla", "KA01AB1234", 50.0));
    rentalSystem.addCar(Car("Honda Civic", "KA02XY5678", 60.0));
    rentalSystem.addCar(Car("Ford Mustang", "KA03CD9999", 100.0));

    int choice;
    do {
        cout << "\nCar Rental System\n";
        cout << "1. Display available cars\n";
        cout << "2. Rent a car\n";
        cout << "3. Return a car\n";
        cout << "4. Display rental history\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            rentalSystem.displayAvailableCars();
            break;
        case 2: {
            int carIndex, days;
            string customerName, contactInfo;
            cout << "Enter customer name: ";
            cin.ignore();
            getline(cin, customerName);
            cout << "Enter contact info: ";
            getline(cin, contactInfo);

            Customer customer(customerName, contactInfo);

            rentalSystem.displayAvailableCars();
            cout << "Enter the car number to rent: ";
            cin >> carIndex;
            cout << "Enter the number of days: ";
            cin >> days;

            rentalSystem.rentCar(carIndex, days, customer);
            break;
        }
        case 3: {
            int recordIndex;
            rentalSystem.displayRentalHistory();
            cout << "Enter the rental record number to return the car: ";
            cin >> recordIndex;

            rentalSystem.returnCar(recordIndex);
            break;
        }
        case 4:
            rentalSystem.displayRentalHistory();
            break;
        case 5:
            cout << "Exiting the system...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
