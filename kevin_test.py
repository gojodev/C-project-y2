import subprocess
from concurrent.futures import ThreadPoolExecutor

# Define the path to your C executable
EXE_PATH = './space_explorer.exe'

MAX_SEED = 5000
fail_count = 0
success_count = 0
total_hops = 0

def process_seed(seed):
    global fail_count, success_count, total_hops
    
    command = [EXE_PATH, str(seed)]
    
    print(f"Processing seed {seed}")
    
    try:
        result = subprocess.run(command, capture_output=True, text=True)
        final_line = result.stdout.strip().split('\n')[-1]
        hops = [int(s) for s in final_line.split() if s.isdigit()]
        
        if len(hops) and hops[0] != 0:
            total_hops += hops[0]
            with open('output.txt', 'a') as output_file:
                output_file.write(f"SEED: [{seed}] | {final_line}\n")
            success_count += 1
        else:
            with open('output.txt', 'a') as output_file:
                output_file.write(f"SEED: [{seed}] | Exceeded max hops. FAILED \n")
            fail_count += 1
            
    except subprocess.CalledProcessError as e:
        print(f"Error executing command with seed {seed}: {e}")

# Using ThreadPoolExecutor to run tasks in parallel
with ThreadPoolExecutor() as executor:
    executor.map(process_seed, range(1, MAX_SEED + 1))

print("Execution completed. Output saved to output.txt.")
if success_count > 0:
    fail_rate = fail_count / (fail_count + success_count)
    print(f"Successes: {success_count}\nFailures: {fail_count}\nSuccess Rate: {100 - (fail_rate * 100):.2f}% ")
    print(f"Average hops: {total_hops / success_count:.1f} ")
else:
    print("No successful executions, so failure rate and average hops cannot be calculated.")