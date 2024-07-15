#if 1

#include <iostream>
#include <string>

// HVAC components
class Thermostat {
public:
    void setSettings(const std::string& settings) {
        // Set thermostat settings
        std::cout << "Thermostat settings: " << settings << std::endl;
    }
};

class HeatPump {
public:
    void setMode(const std::string& mode) {
        // Set heat pump mode
        std::cout << "Heat pump mode: " << mode << std::endl;
    }
};

class AirFilter {
public:
    void installFilter(const std::string& filterType) {
        // Install air filter
        std::cout << "Installed air filter type: " << filterType << std::endl;
    }
};

// HVAC configuration builder
class HVACConfigurationBuilder {
public:
    virtual void buildThermostat() = 0;
    virtual void buildHeatPump() = 0;
    virtual void buildAirFilter() = 0;
};

// Concrete builder for a basic HVAC configuration
class BasicHVACBuilder : public HVACConfigurationBuilder {
private:
    Thermostat thermostat_;
    HeatPump heatPump_;
    AirFilter airFilter_;

public:
    void buildThermostat() override {
        thermostat_.setSettings("Basic settings");
    }

    void buildHeatPump() override {
        heatPump_.setMode("Cooling");
    }

    void buildAirFilter() override {
        airFilter_.installFilter("Standard");
    }
};

// Director (optional)
class HVACSystemDirector {
public:
    void construct(HVACConfigurationBuilder& builder) {
        builder.buildThermostat();
        builder.buildHeatPump();
        builder.buildAirFilter();
    }
};

int main() {
    BasicHVACBuilder basicBuilder;
    HVACSystemDirector director;
    director.construct(basicBuilder);

    // You can access the configured components if needed:
    // basicBuilder.getThermostat();
    // basicBuilder.getHeatPump();
    // basicBuilder.getAirFilter();

    return 0;
}


#endif