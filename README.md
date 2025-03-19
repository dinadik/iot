# Installation Guide for Mosquitto, MySQL, and Apache2

This guide provides step-by-step instructions on how to install Mosquitto (MQTT broker), MySQL (database server), and Apache2 (web server) on a Linux-based system using the terminal.

---

## **Prerequisites**
Ensure your system is updated before proceeding:
```sh
sudo apt update && sudo apt upgrade -y
```

---

## **1. Installing Mosquitto (MQTT Broker)**
Mosquitto is an open-source message broker that implements the MQTT protocol.

### **Installation:**
```sh
sudo apt install -y mosquitto mosquitto-clients
```

### **Enable and Start the Service:**
```sh
sudo systemctl enable mosquitto
sudo systemctl start mosquitto
```

### **Check Mosquitto Status:**
```sh
sudo systemctl status mosquitto
```

### **Test Mosquitto (Optional):**
Open two terminal windows:
1. **Subscriber:**
   ```sh
   mosquitto_sub -h localhost -t test/topic
   ```
2. **Publisher:**
   ```sh
   mosquitto_pub -h localhost -t test/topic -m "Hello, MQTT!"
   ```

---

## **2. Installing MySQL (Database Server)**
MySQL is a widely used relational database management system.

### **Installation:**
```sh
sudo apt install -y mysql-server
```

### **Secure the Installation:**
```sh
sudo mysql_secure_installation
```
Follow the prompts to set a root password and secure the server.

### **Check MySQL Status:**
```sh
sudo systemctl status mysql
```

### **Access MySQL CLI:**
```sh
sudo mysql -u root -p
```

---

## **3. Installing Apache2 (Web Server)**
Apache2 is a widely used web server for hosting websites and applications.

### **Installation:**
```sh
sudo apt install -y apache2
```

### **Enable and Start the Service:**
```sh
sudo systemctl enable apache2
sudo systemctl start apache2
```

### **Check Apache2 Status:**
```sh
sudo systemctl status apache2
```

### **Test Apache Installation:**
Open a web browser and go to:
```
http://localhost
```
If Apache is installed correctly, you should see the default Apache2 Ubuntu welcome page.

---

## **4. Installing FTP Server (vsftpd)**
An FTP server allows file transfers between clients and the server.

### **Installation:**
```sh
sudo apt install -y vsftpd
```

### **Enable and Start the Service:**
```sh
sudo systemctl enable vsftpd
sudo systemctl start vsftpd
```

### **Check FTP Server Status:**
```sh
sudo systemctl status vsftpd
```

### **Configure FTP (Optional):**
To edit the FTP configuration file:
```sh
sudo nano /etc/vsftpd.conf
```
Make necessary changes, save the file, and restart the service:
```sh
sudo systemctl restart vsftpd
```

---

## **5. Installing X Windows System (GUI Interface)**
The X Windows System provides a graphical user interface for Linux.

### **Installation:**
```sh
sudo apt install -y xorg xinit
```

### **Check X Server Version:**
```sh
X -version
```

### **Starting X Windows:**
If you installed a desktop environment like LXDE, XFCE, or GNOME, start it with:
```sh
startx
```

---

## **Additional Notes**
- To **restart services**, use:
  ```sh
  sudo systemctl restart mosquitto
  sudo systemctl restart mysql
  sudo systemctl restart apache2
  sudo systemctl restart vsftpd
  ```
- To **stop services**, use:
  ```sh
  sudo systemctl stop mosquitto
  sudo systemctl stop mysql
  sudo systemctl stop apache2
  sudo systemctl stop vsftpd
  ```
- To **check service logs**, use:
  ```sh
  sudo journalctl -u mosquitto --no-pager
  sudo journalctl -u mysql --no-pager
  sudo journalctl -u apache2 --no-pager
  sudo journalctl -u vsftpd --no-pager
  ```

---

## **Contributing**
Feel free to contribute to this guide by submitting a pull request.

---

## **License**
This project is licensed under the MIT License.
