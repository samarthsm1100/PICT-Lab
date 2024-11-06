import os

print("Partition Recovery Script")

print("List of devices attached to the system:")
os.system("wmic logicaldisk get name")

devname = input("Enter the device letter (e.g., C:, D:):\n")

print("\nShowing partition table:")
os.system(f"diskpart /s partition_list.txt")

with open("partition_list.txt", "w") as f:
    f.write(f"select disk {devname[0]}\n")
    f.write("list partition\n")

os.system("diskpart /s partition_list.txt")

pno = input("Enter the partition number to recover: ")

with open("partition_recover.txt", "w") as f:
    f.write(f"select disk {devname[0]}\n")
    f.write(f"select partition {pno}\n")
    f.write("assign letter=Z\n")
    f.write("active\n")
    f.write("exit\n")

print(f"\nRecovering partition {pno} on {devname}:")
os.system("diskpart /s partition_recover.txt")

print(f"\nPartition {pno} has been recovered and assigned a new drive letter.")