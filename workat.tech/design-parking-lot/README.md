# [Design a Parking Lot](https://workat.tech/machine-coding/practice/design-parking-lot-qm6hwq4wkhp8) | Machine Coding Round Questions (SDE I/II)

## Problem Statement

A parking lot is an area where cars can be parked for a certain amount of time. A parking lot can have multiple floors with each floor having a different number of slots and each slot being suitable for different types of vehicles.

![Parking Lot](https://wat-images.s3.ap-south-1.amazonaws.com/images/machine-coding/parking_lot/parking_lot.jpg)
_Source: [https://commons.wikimedia.org/wiki/File:P3030027ParkingLot_wb.jpg](https://commons.wikimedia.org/wiki/File:P3030027ParkingLot_wb.jpg)_

Design the next generation parking lot system which can manage a parking lot without any human intervention.

## Requirements

Create a command-line application for the parking lot system with the following requirements:

### Core Functions

- Create the parking lot.
- Add floors to the parking lot.
- Add a parking slot to any floor.
- Given a vehicle, find the first available slot, book it, create a ticket, park the vehicle, and return the ticket.
- Unpark a vehicle given the ticket ID.
- Display the number of free slots per floor for a specific vehicle type.
- Display all the free slots per floor for a specific vehicle type.
- Display all the occupied slots per floor for a specific vehicle type.

### Vehicle Details

- Each vehicle has a **type**, **registration number**, and **color**.
- Vehicle types:

  - Car
  - Bike
  - Truck

### Parking Slot Details

- Each slot type can park only a specific vehicle type.
- No other vehicle should be allowed by the system.
- First available slot selection criteria:

  - Slot type matches the vehicle type.
  - Slot is on the lowest possible floor.
  - Slot has the lowest possible slot number on that floor.

- Slots are numbered serially from 1 to _n_ for each floor.

### Parking Lot Floors

- Floors are numbered serially from 1 to _n_.
- Each floor may contain one or more slots of different types.
- Assumption: the first slot on each floor is for a **truck**, the next **2** for **bikes**, and all remaining slots for **cars**.

### Tickets

- Ticket ID format: `<parking_lot_id>_<floor_no>_<slot_no>`
  Example: `PR1234_2_5` (5th slot of 2nd floor of parking lot PR1234)
- Assume only one parking lot with ID `PR1234`.

## Input/Output Format

The code should strictly follow the input/output format and will be tested with provided test cases.

### Input Format

Multiple lines, each containing a command. Possible commands:

- `create_parking_lot <parking_lot_id> <no_of_floors> <no_of_slots_per_floor>`
- `park_vehicle <vehicle_type> <reg_no> <color>`
- `unpark_vehicle <ticket_id>`
- `display <display_type> <vehicle_type>`
  Possible `display_type` values: `free_count`, `free_slots`, `occupied_slots`
- `exit`

Stop taking input when `exit` is encountered.

### Output Format

- **create_parking_lot**
  `Created parking lot with <no_of_floors> floors and <no_of_slots_per_floor> slots per floor`
- **park_vehicle**
  `Parked vehicle. Ticket ID: <ticket_id>`
  Print `Parking Lot Full` if no slot is available for that vehicle type.
- **unpark_vehicle**
  `Unparked vehicle with Registration Number: <reg_no> and Color: <color>`
  Print `Invalid Ticket` if the ticket is invalid or the slot is not occupied.
- **display free_count <vehicle_type>**
  `No. of free slots for <vehicle_type> on Floor <floor_no>: <no_of_free_slots>` (for each floor)
- **display free_slots <vehicle_type>**
  `Free slots for <vehicle_type> on Floor <floor_no>: <comma_separated_slot_numbers>` (for each floor)
- **display occupied_slots <vehicle_type>**
  `Occupied slots for <vehicle_type> on Floor <floor_no>: <comma_separated_slot_numbers>` (for each floor)

## Examples

### Sample Input

```txt
create_parking_lot PR1234 2 6
display free_count CAR
display free_count BIKE
display free_count TRUCK
display free_slots CAR
display free_slots BIKE
display free_slots TRUCK
display occupied_slots CAR
display occupied_slots BIKE
display occupied_slots TRUCK
park_vehicle CAR KA-01-DB-1234 black
park_vehicle CAR KA-02-CB-1334 red
park_vehicle CAR KA-01-DB-1133 black
park_vehicle CAR KA-05-HJ-8432 white
park_vehicle CAR WB-45-HO-9032 white
park_vehicle CAR KA-01-DF-8230 black
park_vehicle CAR KA-21-HS-2347 red
display free_count CAR
display free_count BIKE
display free_count TRUCK
unpark_vehicle PR1234_2_5
unpark_vehicle PR1234_2_5
unpark_vehicle PR1234_2_7
display free_count CAR
display free_count BIKE
display free_count TRUCK
display free_slots CAR
display free_slots BIKE
display free_slots TRUCK
display occupied_slots CAR
display occupied_slots BIKE
display occupied_slots TRUCK
park_vehicle BIKE KA-01-DB-1541 black
park_vehicle TRUCK KA-32-SJ-5389 orange
park_vehicle TRUCK KL-54-DN-4582 green
park_vehicle TRUCK KL-12-HF-4542 green
display free_count CAR
display free_count BIKE
display free_count TRUCK
display free_slots CAR
display free_slots BIKE
display free_slots TRUCK
display occupied_slots CAR
display occupied_slots BIKE
display occupied_slots TRUCK
exit
```

### Expected Output

```txt
Created parking lot with 2 floors and 6 slots per floor
No. of free slots for CAR on Floor 1: 3
No. of free slots for CAR on Floor 2: 3
No. of free slots for BIKE on Floor 1: 2
No. of free slots for BIKE on Floor 2: 2
No. of free slots for TRUCK on Floor 1: 1
No. of free slots for TRUCK on Floor 2: 1
Free slots for CAR on Floor 1: 4,5,6
Free slots for CAR on Floor 2: 4,5,6
Free slots for BIKE on Floor 1: 2,3
Free slots for BIKE on Floor 2: 2,3
Free slots for TRUCK on Floor 1: 1
Free slots for TRUCK on Floor 2: 1
Occupied slots for CAR on Floor 1:
Occupied slots for CAR on Floor 2:
Occupied slots for BIKE on Floor 1:
Occupied slots for BIKE on Floor 2:
Occupied slots for TRUCK on Floor 1:
Occupied slots for TRUCK on Floor 2:
Parked vehicle. Ticket ID: PR1234_1_4
Parked vehicle. Ticket ID: PR1234_1_5
Parked vehicle. Ticket ID: PR1234_1_6
Parked vehicle. Ticket ID: PR1234_2_4
Parked vehicle. Ticket ID: PR1234_2_5
Parked vehicle. Ticket ID: PR1234_2_6
Parking Lot Full
No. of free slots for CAR on Floor 1: 0
No. of free slots for CAR on Floor 2: 0
No. of free slots for BIKE on Floor 1: 2
No. of free slots for BIKE on Floor 2: 2
No. of free slots for TRUCK on Floor 1: 1
No. of free slots for TRUCK on Floor 2: 1
Unparked vehicle with Registration Number: WB-45-HO-9032 and Color: white
Invalid Ticket
Invalid Ticket
No. of free slots for CAR on Floor 1: 0
No. of free slots for CAR on Floor 2: 1
No. of free slots for BIKE on Floor 1: 2
No. of free slots for BIKE on Floor 2: 2
No. of free slots for TRUCK on Floor 1: 1
No. of free slots for TRUCK on Floor 2: 1
Free slots for CAR on Floor 1:
Free slots for CAR on Floor 2: 5
Free slots for BIKE on Floor 1: 2,3
Free slots for BIKE on Floor 2: 2,3
Free slots for TRUCK on Floor 1: 1
Free slots for TRUCK on Floor 2: 1
Occupied slots for CAR on Floor 1: 4,5,6
Occupied slots for CAR on Floor 2: 4,6
Occupied slots for BIKE on Floor 1:
Occupied slots for BIKE on Floor 2:
Occupied slots for TRUCK on Floor 1:
Occupied slots for TRUCK on Floor 2:
Parked vehicle. Ticket ID: PR1234_1_2
Parked vehicle. Ticket ID: PR1234_1_1
Parked vehicle. Ticket ID: PR1234_2_1
Parking Lot Full
No. of free slots for CAR on Floor 1: 0
No. of free slots for CAR on Floor 2: 1
No. of free slots for BIKE on Floor 1: 1
No. of free slots for BIKE on Floor 2: 2
No. of free slots for TRUCK on Floor 1: 0
No. of free slots for TRUCK on Floor 2: 0
Free slots for CAR on Floor 1:
Free slots for CAR on Floor 2: 5
Free slots for BIKE on Floor 1: 3
Free slots for BIKE on Floor 2: 2,3
Free slots for TRUCK on Floor 1:
Free slots for TRUCK on Floor 2:
Occupied slots for CAR on Floor 1: 4,5,6
Occupied slots for CAR on Floor 2: 4,6
Occupied slots for BIKE on Floor 1: 2
Occupied slots for BIKE on Floor 2:
Occupied slots for TRUCK on Floor 1: 1
Occupied slots for TRUCK on Floor 2: 1
```

## Expectations

- Working and demonstrable code.
- Functionally correct implementation.
- Modular and readable code.
- Clear separation of concerns.
- Avoid putting everything in a single file (except when coding in C/C++).
- Easy to accommodate new requirements with minimal changes.
- A main method from where the code can be easily tested.
- No need for a GUI.

## Optional Requirements

_Do these only if time permits. Write code so these can be added without major changes._

- Unit tests if possible.
- Extensible to add new vehicle and slot types.
- Extensible to allow different strategies for finding the first available slot.
- Extensible to handle additional commands.
- Extensible to support multiple parking lots (input/output format can be changed for that).
- Thread-safe to handle concurrent requests.
