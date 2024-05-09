//
// Created by A413098 on 07/05/2024.
//

#ifndef LASD_ESERCIZIO1_ZMYTEST_UTILS_AUTOMOBILE_HPP_
#define LASD_ESERCIZIO1_ZMYTEST_UTILS_AUTOMOBILE_HPP_
class Automobile {

 public:
    enum class CarType { SEDAN, SUV, COUPE, HATCHBACK, CONVERTIBLE, STATION_WAGON, PICKUP, VAN, TRUCK, BUS, MOTORCYCLE};

 protected:
    unsigned int yearOfProduction{0};

    CarType carType{CarType::SEDAN};

    std::string brand{""};

    std::string model{""};

    std::string licensePlate{""};

 public:
    Automobile() = default;

    Automobile(unsigned int y, CarType ct, std::string b, std::string m, std::string lp)
        : yearOfProduction(y), carType(ct), brand(b), model(m) {
        setLicensePlate(lp);
    }

    Automobile(const Automobile &other) = default;

    Automobile(Automobile &&other) = default;

    Automobile &operator=(const Automobile &other) {
        //std::cout << "eseguo Automobile = const" << std::endl;
        yearOfProduction = other.yearOfProduction;
        carType = other.carType;
        brand = other.brand;
        model = other.model;
        licensePlate = other.licensePlate;

        return *this;
    }

    Automobile &operator=(Automobile &&other) {
        //std::cout << "eseguo Automobile = &&" << std::endl;
        yearOfProduction = std::move(other.yearOfProduction);
        carType = std::move(other.carType);
        brand = std::move(other.brand);
        model = std::move(other.model);
        licensePlate = std::move(other.licensePlate);

        return *this;
    }

    ~Automobile() = default;

    bool operator==(const Automobile &other) const {
        return yearOfProduction == other.yearOfProduction && carType == other.carType && brand == other.brand &&
            model == other.model && licensePlate == other.licensePlate;
    }

    bool operator!=(const Automobile &other) const { return !(*this == other); }

    bool operator<(const Automobile &other) const {
        return yearOfProduction < other.yearOfProduction || (brand + model < other.brand + other.model) ||
            licensePlate < other.licensePlate;
    }

    // ... altri operatori di confronto ...

    friend inline std::ostream &operator<<(std::ostream &os, const Automobile &a) {
        os
            << "Brand: "
            << a.brand
            << " Model: "
            << a.model
            << " Year of Production: "
            << a.yearOfProduction;
        return os;
    }

    std::string getBrand() const { return brand; }

    void setBrand(const std::string &newBrand) { brand = newBrand; }

    std::string getModel() const { return model; }

    void setModel(const std::string &newModel) { model = newModel; }

    std::string getLicensePlate() const { return licensePlate; }

    void setLicensePlate(const std::string &newLicensePlate) {
        if (isValidLicensePlate(newLicensePlate))
            licensePlate = newLicensePlate;
    }

    unsigned int getYearOfProduction() const { return yearOfProduction; }
    void setYearOfProduction(unsigned int newYearOfProduction) { yearOfProduction = newYearOfProduction; }

    CarType getCarType() const { return carType; }
    void setCarType(CarType newCarType) { carType = newCarType; }

 private:
    bool isValidLicensePlate(const std::string &lp) const noexcept {
        if (lp.length() != 7) {
            return false;
        }

        return true;
    }
};
#endif //LASD_ESERCIZIO1_ZMYTEST_UTILS_AUTOMOBILE_HPP_
