import tkinter as tk
from tkinter import ttk
import socket
import time
import subprocess
 
class PumpControlGUI:
    def __init__(self, root):
        self.host = '10.0.0.251'
        self.port = 80
 
        self.root = root
        self.primary_bg = "#ecf0f1"
        self.secondary_bg = "#a6c1ee"
        self.button_bg = "#6792e0"
        self.text_color = "#212121"
        self.root.configure(bg=self.primary_bg)
        self.root.title("Pump Control")
        self.root.geometry("800x480")
 
        self.pump_controls = {}
        self.is_timer_running = {}
        self.start_time = {}
 
        self.drugs = ['Abatacept', 'Abiciximab', 'Acetaminophen', 'AcetaZOLAMIDE', 'Acetylcystein']
 
        self.create_home_screen()
 
    def create_home_screen(self):
        self.clear_screen()
        header = tk.Label(self.root, text="Pump Control Dashboard", font=("Helvetica", 18), bg=self.primary_bg, fg=self.text_color)
        header.pack(pady=5)
 
        # Parent frame for all pumps
        parent_frame = tk.Frame(self.root, bg=self.primary_bg)
        parent_frame.pack(expand=True, fill="both", padx=5)
 
        def close_keyboard(event=None):
            subprocess.run(["pkill", "wvkbd"])
            subprocess.run(["pkill", "wvkbd-mobintl"])
            
 
        # Bind Enter key to close the keyboard
        self.root.bind("<Return>", close_keyboard)
 
        for i, pump in enumerate(["A", "B", "C", "D"]):
            # Each pump panel
            frame = tk.Frame(parent_frame, bg=self.secondary_bg, padx=5, pady=5, relief="raised", bd=2)
            frame.grid(row=0, column=i, padx=5, pady=5, sticky="nsew")
 
            self.create_pump_controls(frame, pump)
 
    def create_pump_controls(self, frame, pump):
        tk.Label(frame, text=f"Pump {pump}", font=("Helvetica", 14), bg=self.secondary_bg, fg=self.text_color).pack(pady=2)
 
        # Dropdown for drug selection
        tk.Label(frame, text="Drug:", font=("Arial", 12), bg=self.secondary_bg, fg=self.text_color).pack(pady=2)
        drug_var = tk.StringVar()
        drug_dropdown = ttk.Combobox(frame, textvariable=drug_var, values=self.drugs, state="readonly", width=12)
        drug_dropdown.pack(pady=2)
 
        # Volume entry
        tk.Label(frame, text="Volume (mL):", font=("Arial", 12), bg=self.secondary_bg, fg=self.text_color).pack(pady=2)
        volume_entry = tk.Entry(frame, width=15)
        volume_entry.pack(pady=2)
 
        # Duration (hrs and mins)
        tk.Label(frame, text="Duration (hrs):", font=("Arial", 12), bg=self.secondary_bg, fg=self.text_color).pack(pady=2)
        duration_hrs_entry = tk.Entry(frame, width=15)
        duration_hrs_entry.pack(pady=2)
 
        tk.Label(frame, text="Duration (mins):", font=("Arial", 12), bg=self.secondary_bg, fg=self.text_color).pack(pady=2)
        duration_mins_entry = tk.Entry(frame, width=15)
        duration_mins_entry.pack(pady=2)
 
        # Dose and rate labels
        dose_label = tk.Label(frame, text="Dose: ___ mg", font=("Arial", 12), bg=self.secondary_bg, fg=self.text_color)
        dose_label.pack(pady=2)
        rate_label = tk.Label(frame, text="Rate: ___ mL/h", font=("Arial", 12), bg=self.secondary_bg, fg=self.text_color)
        rate_label.pack(pady=2)
 
        # Start/Stop button
        start_stop_button = tk.Button(frame, text="Start Infusion", font=("Arial", 12), bg=self.button_bg, fg=self.text_color,
                                      activebackground="#2980b9", command=lambda: self.toggle_infusion(pump, start_stop_button))
        start_stop_button.pack(pady=2)
 
        # Timer label
        timer_label = tk.Label(frame, text="Timer: 0s", font=("Arial", 12), bg=self.secondary_bg, fg=self.text_color)
        timer_label.pack(pady=2)
 
        # Save controls for each pump
        self.pump_controls[pump] = {
            'drug_dropdown': drug_dropdown,
            'volume_entry': volume_entry,
            'duration_hrs_entry': duration_hrs_entry,
            'duration_mins_entry': duration_mins_entry,
            'dose_label': dose_label,
            'rate_label': rate_label,
            'timer_label': timer_label,
            'start_stop_button': start_stop_button
        }
        self.is_timer_running[pump] = False
        self.start_time[pump] = None
 
        # Bind keyboard for specific fields
        volume_entry.bind("<Button-1>", self.open_keyboard)
        duration_hrs_entry.bind("<Button-1>", self.open_keyboard)
        duration_mins_entry.bind("<Button-1>", self.open_keyboard)
 
    def open_keyboard(self, event=None):
        subprocess.Popen(['wvkbd-mobintl'])
 
    def toggle_infusion(self, pump, button):
        if not self.is_timer_running[pump]:
            self.start_infusion(pump, button)
        else:
            self.stop_infusion(pump, button)
 
    def start_infusion(self, pump, button):
        controls = self.pump_controls[pump]
        try:
            drug_amount = controls['drug_dropdown'].get()
            vtbi = float(controls['volume_entry'].get())
            hrs = float(controls['duration_hrs_entry'].get()) if controls['duration_hrs_entry'].get() else 0
            mins = float(controls['duration_mins_entry'].get()) if controls['duration_mins_entry'].get() else 0
            total_duration_hrs = hrs + mins / 60
            rate = vtbi / total_duration_hrs if total_duration_hrs > 0 else 0
 
            controls['dose_label'].config(text=f"Dose: {drug_amount} mg")
            controls['rate_label'].config(text=f"Rate: {rate:.2f} mL/h")
 
            self.is_timer_running[pump] = True
            self.start_time[pump] = time.time()
            self.update_timer(pump)
 
            # Change button to "Stop Infusion"
            button.config(text="Stop Infusion", command=lambda: self.stop_infusion(pump, button))
 
        except ValueError:
            print(f"Please enter valid numbers for Pump {pump}.")
 
    def stop_infusion(self, pump, button):
        self.is_timer_running[pump] = False
        self.pump_controls[pump]['timer_label'].config(text="Timer: Stopped")
        button.config(text="Start Infusion", command=lambda: self.start_infusion(pump, button))
 
    def update_timer(self, pump):
        if self.is_timer_running[pump]:
            elapsed_time = int(time.time() - self.start_time[pump])
            self.pump_controls[pump]['timer_label'].config(text=f"Timer: {elapsed_time}s")
            self.root.after(1000, lambda: self.update_timer(pump))
 
    def clear_screen(self):
        for widget in self.root.winfo_children():
            widget.destroy()
 
 
    def send_message(self, IP, msg):
        """Send a message to the pump via socket."""
        try:
            with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
                s.connect((IP, self.port))
                s.sendall(msg)
                data = s.recv(1024)
                print("Received:", data)
        except socket.error as e:
            print(f"Socket error: {e}")
 
    def start_infusion(self, pump, button):
        controls = self.pump_controls[pump]
        try:
            drug_amount = controls['drug_dropdown'].get()
            vtbi = float(controls['volume_entry'].get())
            hrs = float(controls['duration_hrs_entry'].get()) if controls['duration_hrs_entry'].get() else 0
            mins = float(controls['duration_mins_entry'].get()) if controls['duration_mins_entry'].get() else 0
            total_duration_hrs = hrs + mins / 60
            rate = vtbi / total_duration_hrs if total_duration_hrs > 0 else 0
 
            controls['dose_label'].config(text=f"Dose: {drug_amount} mg")
            controls['rate_label'].config(text=f"Rate: {rate:.2f} mL/h")
 
            self.is_timer_running[pump] = True
            self.start_time[pump] = time.time()
            self.update_timer(pump)
 
            # Change button to "Stop Infusion"
            button.config(text="Stop Infusion", command=lambda: self.stop_infusion(pump, button))
 
            # Prepare and send the infusion details to the pump
            self.print_and_send_data(pump, drug_amount, vtbi, rate)
 
        except ValueError:
            print(f"Please enter valid numbers for Pump {pump}.")
 
    def print_and_send_data(self, pump, drug, vtbi, rate):
        """Prepare a message to send and send it to the correct pump based on its letter."""
        # Map pumps to their respective IPs
        pump_ip_map = {
            "A": '10.3.141.193',
            "B": '10.3.141.141',
            "C": '10.3.141.244',
            "D": '10.3.141.197'
        }
 
        # Calculate the scaled rate
        scaled_rate = rate / 200
        done = round(scaled_rate, 2)
        print(f"Scaled rate for Pump {pump}: {done}")
 
        # Determine the IP address of the selected pump
        ip = pump_ip_map.get(pump)
        if not ip:
            print(f"No IP configured for Pump {pump}.")
            return
 
        # Prepare the message based on the scaled rate
        if done > 9:
            message = b'ten\n'
        elif done > 8:
            message = b'nine\n'
        elif done > 7:
            message = b'eight\n'
        elif done > 6:
            message = b'seven\n'
        elif done > 5:
            message = b'six\n'
        elif done > 4:
            message = b'five\n'
        elif done > 3:
            message = b'four\n'
        elif done > 2:
            message = b'three\n'
        elif done > 1:
            message = b'two\n'
        elif done > 0:
            message = b'one\n'
        else:
            message = b'zero\n'
 
        # Print infusion details for debugging
        print(f"Infusion Details for Pump {pump}:\nDrug: {drug}\nVTBI: {vtbi} mL\nRate: {rate:.2f} mL/h")
        print(f"Sending to IP {ip}: {message.decode().strip()}")
 
        # Send the message to the pump
        self.send_message(ip, message)
 
root = tk.Tk()
app = PumpControlGUI(root)
root.mainloop()
