import pandas as pd
import matplotlib.pyplot as plt


def graph_test(file, title):
    try:
        df = pd.read_csv(file)
        if df.empty:
            raise ValueError("Empty CSV")

        plt.figure()
        plt.plot(df["height_km"], df["expected"], label="Expected")
        plt.plot(df["height_km"], df["actual"], label="Actual")
        plt.xlabel("Height (km)")
        plt.ylabel("Temperature (C)")
        plt.title(title)
        plt.legend()
        plt.show()

    except (pd.errors.EmptyDataError, FileNotFoundError, ValueError) as e:
        print(f"Skipping plot for '{title}': {e}")

    finally:
        plt.close()


graph_test(r"C:\clionProject\ISA_Rafael\test1.csv", "Test 1 - ISA Comparison")
graph_test(r"C:\clionProject\ISA_Rafael\test2.csv", "Test 2 - ISA Comparison")
graph_test(r"C:\clionProject\ISA_Rafael\test3.csv", "Test 3 - ISA Comparison")

def graph_error(file, title):
    try:
        df = pd.read_csv(file)
        if df.empty:
            raise ValueError("Empty CSV")

        plt.figure()

        plt.plot(df["height_km"], df["error"])

        plt.xlabel("Height (km)")
        plt.ylabel("Error (C)")
        plt.title(title)

        plt.show()

    except (pd.errors.EmptyDataError, FileNotFoundError, ValueError) as e:
        print(f"Skipping plot for '{title}': {e}")

    finally:
        plt.close()


graph_error(r"C:\clionProject\ISA_Rafael\test1.csv", "Test 1 - Error Measurement")
graph_error(r"C:\clionProject\ISA_Rafael\test2.csv", "Test 2 - Error Measurement")
graph_error(r"C:\clionProject\ISA_Rafael\test3.csv", "Test 3 - Error Measurement")