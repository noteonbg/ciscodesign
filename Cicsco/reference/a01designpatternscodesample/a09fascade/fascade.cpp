#include <iostream>

#if 1

// Subsystem 1: Engine (Heating/Cooling)
class Engine {
public:
    void Start() {
        std::cout << "Engine started" << std::endl;
    }
    void Stop() {
        std::cout << "Engine stopped" << std::endl;
    }
};

// Subsystem 2: Lights
class Lights {
public:
    void TurnOn() {
        std::cout << "Lights on" << std::endl;
    }
    void TurnOff() {
        std::cout << "Lights off" << std::endl;
    }
};

// Subsystem 3: Thermostat
class Thermostat {
public:
    void SetTemperature(int temp) {
        std::cout << "Temperature set to " << temp << "°C" << std::endl;
    }
};



// HVAC Facade - you can put an interface in between also if need be..
class HVACSystem {
private:
    Engine engine;
    Lights lights;
    Thermostat thermostat;

public:
    void StartHVAC() {
        engine.Start();
        lights.TurnOn();
        thermostat.SetTemperature(22); // Set desired temperature
        std::cout << "HVAC system started" << std::endl;
    }

    void StopHVAC() {
        lights.TurnOff();
        engine.Stop();
        std::cout << "HVAC system stopped" << std::endl;
    }
};

int main() {
    HVACSystem hvac;
    hvac.StartHVAC(); // Start the HVAC system
    // Simulate some operation...
    hvac.StopHVAC(); // Stop the HVAC system
    return 0;
}

#endif