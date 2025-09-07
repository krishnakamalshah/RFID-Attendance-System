# 📌 RFID-Based Smart Attendance System

An **IoT-based Attendance Management System** built with **Arduino** and an **RFID module (MFRC522)**.  
This project automates check-in/check-out processes using RFID cards, provides **real-time feedback via LCD display**, and logs attendance data in **CSV format** through the Serial Monitor for easy integration with Excel/Google Sheets.

---

## 🚀 Features
- ✅ **RFID Authentication** – Detects and validates card UIDs against a whitelist database.  
- ✅ **Attendance Tracking** – Toggles between **Check-In** and **Check-Out** for each user.  
- ✅ **LCD Feedback** – Displays user-friendly messages (Welcome, Goodbye, Access Denied).  
- ✅ **Data Logging** – Exports structured attendance logs to Serial in CSV format.  
- ✅ **Expandable Design** – Can be scaled for classrooms, offices, or secure access control.  

---

## 🛠️ Tech Stack

**Hardware:**
- Arduino UNO / MEGA  
- RFID Reader (MFRC522)  
- I²C 16x2 LCD Display  
- RFID Tags / Cards  

**Software & Libraries:**
- Arduino IDE (C/C++)  
- [SPI.h](https://www.arduino.cc/en/reference/SPI)  
- [MFRC522.h](https://github.com/miguelbalboa/rfid)  
- [Wire.h](https://www.arduino.cc/en/reference/wire)  
- [LiquidCrystal_I2C.h](https://github.com/johnrickman/LiquidCrystal_I2C)  

---

## ⚙️ Circuit Diagram (Overview)

- **RFID Module → Arduino** (via SPI: MOSI, MISO, SCK, SS, RST)  
- **LCD → Arduino** (via I²C: SDA, SCL)  
- **Power Supply**: 5V from Arduino  

*(You can draw and add a schematic image here later for clarity.)*

---

## 📂 Project Structure
📦 RFID-Attendance-System
┣ 📜 RFID_code.ino # Main Arduino code
┣ 📜 README.md # Documentation (this file)


---

## ▶️ Getting Started

### 1️⃣ Clone this Repository
git clone https://github.com/your-username/RFID-Attendance-System.git

2️⃣ Install Libraries

In Arduino IDE, install the following libraries via Library Manager:

MFRC522

LiquidCrystal_I2C

3️⃣ Upload the Code

Connect your Arduino board via USB.

Open RFID_code.ino in Arduino IDE.

Select the correct board and port.

Upload the sketch.

4️⃣ Test the System

Power the Arduino and LCD.

Scan an RFID card:

If valid → LCD shows Welcome or Goodbye.

If invalid → LCD shows Access Denied.

Open Serial Monitor (9600 baud) to view attendance logs.

📝 Sample Serial Output
CLEARDATA
LABEL, Time, Card ID, Name, Status, Time IN, Time OUT
RESETTIMER
DATA, TIME, EC75C71, Krishna, Present, TIME, 
DATA, TIME, EC75C71, Krishna, Exited, , TIME
DATA, TIME, C77372, Ravi, Present, TIME, 

📌 Future Improvements

🔗 Integrate with cloud database (Firebase/ThingSpeak/MySQL) for persistent storage.

📱 Build a mobile/web dashboard for real-time monitoring.

⏰ Add an RTC (Real-Time Clock) module for accurate timestamp logging.

📊 Generate automated reports from attendance logs.

👨‍💻 Author

Developed by Krishna Kamal Shah
📧 Contact: krishnakamalshah.com

🌐 Portfolio: https://github.com/krishnakamalshah/portfolio

📜 License

This project is licensed under the MIT License – feel free to use and modify with attribution.
