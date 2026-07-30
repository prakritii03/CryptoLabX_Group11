import os
from datetime import datetime
from collections import Counter


LOG_FILE = "crypto.log"
DATASET_FOLDER = "datasets"


def log_menu_selection(option):
    """Record the selected menu option with date and time."""
    current_time = datetime.now().strftime("%Y-%m-%d %H:%M:%S")

    with open(LOG_FILE, "a", encoding="utf-8") as log:
        log.write(f"{current_time} | Selected Option: {option}\n")


def analyze_file():
    """Read a text file from datasets and display basic statistics."""

    print("\n--- File Analysis ---")

    filename = input("Enter dataset filename (example: text1.txt): ").strip()

    filepath = os.path.join(DATASET_FOLDER, filename)

    if not os.path.isfile(filepath):
        print("File not found in datasets folder.")
        return

    try:
        with open(filepath, "r", encoding="utf-8") as file:
            text = file.read()

        # Number of characters
        character_count = len(text)

        # Number of words
        word_count = len(text.split())

        # Number of lines
        line_count = len(text.splitlines())

        # Number of unique characters
        unique_characters = len(set(text))

        # Letter frequency
        letters = [
            character.lower()
            for character in text
            if character.isalpha()
        ]

        frequency = Counter(letters)

        print("\n===== File Analysis Result =====")
        print(f"File: {filename}")
        print(f"Number of characters: {character_count}")
        print(f"Number of words: {word_count}")
        print(f"Number of lines: {line_count}")
        print(f"Number of unique characters: {unique_characters}")

        print("\nLetter Frequency:")

        for letter in sorted(frequency):
            print(f"{letter}: {frequency[letter]}")

        print("================================")

    except Exception as error:
        print(f"Error while reading file: {error}")


def display_menu():
    """Display the CryptoLabX main menu."""

    while True:
        print("\n")
        print("          CryptoLabX Toolkit")
        print("1. Encrypt")
        print("2. Decrypt")
        print("3. Attack")
        print("4. Analyze")
        print("5. Exit")

        choice = input("Enter your choice: ").strip()

        if choice == "1":
            log_menu_selection("Encrypt")
            print("\nEncrypt: Coming Soon")

        elif choice == "2":
            log_menu_selection("Decrypt")
            print("\nDecrypt: Coming Soon")

        elif choice == "3":
            log_menu_selection("Attack")
            print("\nAttack: Coming Soon")

        elif choice == "4":
            log_menu_selection("Analyze")
            analyze_file()

        elif choice == "5":
            log_menu_selection("Exit")
            print("\nThank you for using CryptoLabX!")
            break

        else:
            log_menu_selection(f"Invalid Option ({choice})")
            print("\nInvalid choice. Please select 1-5.")


if __name__ == "__main__":
    display_menu()