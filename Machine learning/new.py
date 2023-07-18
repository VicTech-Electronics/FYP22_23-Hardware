import csv

input_file = 'csv_data_file.csv'
output_file = 'output.csv'

with open(input_file, 'r') as file:
    reader = csv.reader(file)
    header = next(reader)  # Read the header row

    # Remove the last column from the header
    header = header[:-1]

    with open(output_file, 'w', newline='') as output:
        writer = csv.writer(output)
        writer.writerow(header)  # Write the updated header to the output file

        for row in reader:
            # Remove the last column from each row
            row = row[:-1]
            writer.writerow(row)  # Write the updated row to the output file
