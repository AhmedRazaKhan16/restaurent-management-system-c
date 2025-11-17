# Royal Hotel Management System

A comprehensive console-based Hotel Management System written in C that handles meal ordering, table and room bookings, user management, and sales reporting.

## 📋 Table of Contents

- [Overview](#overview)
- [Features](#features)
- [System Requirements](#system-requirements)
- [Installation](#installation)
- [Usage](#usage)
- [User Roles](#user-roles)
- [Data Storage](#data-storage)
- [Module Details](#module-details)
- [Code Structure](#code-structure)
- [Limitations](#limitations)
- [Future Enhancements](#future-enhancements)

## 🏨 Overview

The Royal Hotel Management System is a console-based application designed to streamline hotel operations including food ordering, table reservations, room bookings, and administrative tasks. The system maintains separate interfaces for administrators and regular users with appropriate permissions.

## ✨ Features

### 🔐 Authentication System
- User registration and login
- Role-based access control (Admin/User)
- Secure credential storage

### 👨‍💼 Admin Features
- **Meal Management**
  - Add new meals to the menu
  - View all available meals
  - Update meal details (name, price)
  - Delete meals (soft delete)
  
- **Sales Reporting**
  - View complete sales history
  - Calculate total revenue
  - Order details with user information
  
- **Booking Management**
  - Monitor table bookings status
  - Track room occupancy
  - View booking history

### 👤 User Features
- **Food Ordering**
  - Browse available meals
  - Place orders with quantity selection
  - Option to associate orders with table/room
  
- **Table Reservations**
  - View available tables
  - Book tables for dining
  
- **Room Bookings**
  - Check room availability
  - Reserve hotel rooms
  
- **Billing**
  - View personal order history
  - Generate itemized bills
  - Calculate total charges

## 🛠 System Requirements

### Software Requirements
- C Compiler (GCC recommended)
- Any operating system supporting ANSI C
- Standard C libraries (stdio.h, stdlib.h, string.h, ctype.h)

### Hardware Requirements
- Minimal system resources
- Sufficient storage for data files
- Basic input/output capabilities

## 📥 Installation

1. **Compile the Source Code**
   ```bash
   gcc -o hotel_management hotel_management.c


This README.md provides comprehensive documentation for the Royal Hotel Management System code, including:
- Complete feature overview
- Detailed installation and usage instructions
- Code structure explanation with data structures and functions
- Technical specifications and limitations
- Troubleshooting guide
- Future enhancement possibilities

The documentation is formatted in markdown with clear sections and should help users understand, compile, and use the system effectively.

