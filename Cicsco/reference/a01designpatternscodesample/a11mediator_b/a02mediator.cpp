#if 1

/*

By using the Mediator Pattern, we’ve decoupled the components, 
allowing them to communicate indirectly through the mediator

*/

class HVACMediator {
public:
    virtual void notifyTemperatureChange(double temperature) = 0;
    virtual void notifyFilterChange(bool filterClean) = 0;
    // Add other notification methods
};


class HVACController : public HVACMediator {
private:
    Thermostat* thermostat_;
    HeatPump* heatPump_;
    AirFilter* airFilter_;

public:
    void setComponents(Thermostat* thermostat, HeatPump* heatPump, AirFilter* airFilter) {
        thermostat_ = thermostat;
        heatPump_ = heatPump;
        airFilter_ = airFilter;
    }

    void notifyTemperatureChange(double temperature) override {
        // Adjust heat pump settings based on temperature
        heatPump_->adjustTemperature(temperature);
    }

    void notifyFilterChange(bool filterClean) override {
        // Alert thermostat if filter needs replacement
        if (!filterClean) {
            thermostat_->displayFilterAlert();
        }
    }
    // Implement other notification methods
};


class Thermostat {
public:
    void setMediator(HVACMediator* mediator) { /* ... */ }
    void displayFilterAlert() { /* ... */ }
    // Other methods
};

class HeatPump {
public:
    void setMediator(HVACMediator* mediator) { /* ... */ }
    void adjustTemperature(double temperature) { /* ... */ }
    // Other methods
};

class AirFilter {
public:
    void setMediator(HVACMediator* mediator) { /* ... */ }
    // Other methods
};


int main() {
    HVACController controller;
    Thermostat thermostat;
    HeatPump heatPump;
    AirFilter airFilter;

    controller.setComponents(&thermostat, &heatPump, &airFilter);

    // Simulate temperature change
    controller.notifyTemperatureChange(22.5);

    // Simulate filter status change
    controller.notifyFilterChange(false);

    return 0;
}


#endif

