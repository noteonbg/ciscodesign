### 1.4. Deployment Diagram ###
Represents association between logical artifacts and physical devices.

#### 1.4.1. Node ####

A physical machine, device, environment and etc., 

![Class](notation/deployment/deployment-1.png)

#### 1.4.2. Node Relations ####

A component might be deployed on to a node.

![Class](notation/deployment/deployment-2.png)

An artifact like configuration file and etc., might be deploed on to a node.

![Class](notation/deployment/deployment-3.png)

Two nodes might be connected physically via network and etc., 

![Class](notation/deployment/deployment-4.png)

#### 1.4.3. Deployment Diagram Illustration ####
![Class](notation/deployment/deployment-5.png)


@startuml
node "HVAC Controller" as controller {
    component "HVACController" as hvacController
}

node "Thermostat Node" as thermostatNode {
    component "Thermostat" as thermostat
}

node "Heat Pump Node" as heatPumpNode {
    component "HeatPump" as heatPump
}

node "Air Filter Node" as airFilterNode {
    component "AirFilter" as airFilter
}

controller --> thermostatNode
controller --> heatPumpNode
controller --> airFilterNode
@enduml

![Class](notation/deployment/plantumldeployment.png)