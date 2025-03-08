# 🔑 RFID-Based Automatic Gate System  

This project is an **RFID-based automatic gate system** that controls access using **RFID cards, an ultrasonic sensor, and a servo motor**. The system grants or denies entry based on RFID card validation, making it suitable for **theme parks, restricted areas, or automated access control**.  

---

## 📌 Features  
- ✅ **RFID authentication** to allow or deny access.  
- 📊 **Ultrasonic sensor** to detect nearby objects and manage gate closing.  
- 🔔 **Buzzer alert** when unauthorized access is attempted.  
- 🔄 **Automatic gate operation** using a **servo motor**.  
- 📺 **16x2 LCD display** for status updates.  

---

## 🛠️ Components Used  
| Component | Description |  
|-----------|------------|  
| **Arduino UNO** | Microcontroller board |  
| **MFRC522 RFID Module** | Reads RFID cards for access control |  
| **HC-SR04 Ultrasonic Sensor** | Detects objects and ensures the gate closes properly |  
| **Servo Motor** | Controls the gate opening and closing |  
| **16x2 LCD (I2C)** | Displays access status messages |  
| **Buzzer** | Alerts unauthorized access attempts |  
| **LEDs (Red & Green)** | Indicate whether access is granted or denied |  

---

## 🔄 How It Works  
1️⃣ **User approaches the gate** → The **ultrasonic sensor** detects their presence.  
2️⃣ **User taps an RFID card** on the **MFRC522 reader**.  
3️⃣ **System checks access permissions**:  
   - ✅ If **the card is valid**, the **green LED turns on**, LCD displays **"Silahkan Masuk!"**, and the **gate opens**.  
   - ❌ If **the card was already used**, the **red LED and buzzer activate**, and LCD displays **"Anda Telah Menaiki Wahana"**.  
4️⃣ **Gate closes automatically** after a short delay.  

---
