#!/bin/bash

# Function to display section headers
function section_header() {
    echo "-------------------------------------------------------------"
    echo "$1"
    echo "-------------------------------------------------------------"
}

current_date=$(date "+%Y-%m-%d %H:%M:%S")
username=$(whoami)
hostname=$(hostname)

section_header "System Information"
echo "Date: $current_date"
echo "Username: $username"
echo "Hostname: $hostname"

section_header "Processor Information"
processor_model=$(lscpu | grep "Model name" | awk -F ':' '{print $2}' | sed 's/^[ \t]*//')
processor_architecture=$(lscpu | grep "Architecture" | awk -F ':' '{print $2}' | sed 's/^[ \t]*//')
max_cpu_frequency=$(lscpu | grep "CPU max MHz" | awk -F ':' '{print $2}' | sed 's/^[ \t]*//')
current_cpu_frequency=$(lscpu | grep "CPU MHz" | awk -F ':' '{print $2}' | sed 's/^[ \t]*//')
num_cores=$(lscpu | grep "Core(s) per socket" | awk -F ':' '{print $2}' | sed 's/^[ \t]*//')
num_threads=$(lscpu | grep "Thread(s) per core" | awk -F ':' '{print $2}' | sed 's/^[ \t]*//')
cpu_usage=$(top -bn1 | grep "Cpu(s)" | awk '{print $2}' | cut -d'%' -f1)

echo "Model: $processor_model"
echo "Architecture: $processor_architecture"
echo "Max CPU Frequency: $max_cpu_frequency MHz"
# echo "Current CPU Frequency: $current_cpu_frequency MHz"
echo "Number of Cores: $num_cores"
echo "Number of Threads per Core: $num_threads"
echo "CPU Usage: $cpu_usage%"

section_header "Memory Information"
mem_info_total=$(free -h | grep "Mem" | awk '{print $2}')
mem_info_free=$(free -h | grep "Mem" | awk '{print $7}')
cache_l1=$(lscpu | grep "L1d cache" | awk '{print $3}')
cache_l2=$(lscpu | grep "L2 cache" | awk '{print $3}')
cache_l3=$(lscpu | grep "L3 cache" | awk '{print $3}')

echo "Memory Info:"
echo "Total: $mem_info_total"
echo "Free: $mem_info_free"
echo "L1 Cache: $cache_l1"
echo "L2 Cache: $cache_l2"
echo "L3 Cache: $cache_l3"

section_header "Disk Information"
disk_info_total=$(df -h / | grep "/dev/nvme0n1p4" | awk '{print $2}')
disk_info_avail=$(df -h / | grep "/dev/nvme0n1p4" | awk '{print $3}')
num_partitions=$(lsblk -l | grep -c 'part')
unallocated_space=$(parted -l 2>/dev/null | grep "Unallocated" | awk '{print $3}')

echo "Disk Info:"
echo "Total: $disk_info_total"
echo "Available: $disk_info_avail"
echo "Total Partitions: $num_partitions"
echo "Unallocated Space: $unallocated_space"

section_header "Swap Information"
swap_info=$(free -h | grep "Swap")
echo "Swap Info:"
echo "$swap_info"

section_header "Network Interfaces"
num_interfaces=$(ifconfig -a | grep -o "^[a-zA-Z0-9]*" | wc -l)
interface_info=$(ifconfig -a | grep -E "^[a-zA-Z0-9]+:")

echo "Number of Network Interfaces: $num_interfaces"
echo "Interface Info:"
echo "$interface_info"
