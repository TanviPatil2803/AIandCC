# Define responses for the chatbot
responses = {
    "hi": "Hello! How can I assist you?",
    "how are you": "I'm doing well, thank you for asking!",
    "bye": "Goodbye! Have a great day!",
    "default": "I'm sorry, I don't understand. Can you please rephrase?"
}

# Function to get the bot's response based on user input
def get_response(user_input):
    user_input = user_input.lower()  # Convert input to lowercase for case insensitivity

    # Check if the user input matches any key in the responses dictionary
    for key in responses:
        if key in user_input:
            return responses[key]

    # If no match is found, return the default response
    return responses["default"]

# Main loop for chatting with the bot
def main():
    print("Chatbot: Hello! How can I assist you? (Type 'bye' to exit)")

    while True:
        user_input = input("You: ")
        if user_input.lower() == "bye":
            print("Chatbot:", responses["bye"])
            break
        else:
            response = get_response(user_input)
            print("Chatbot:", response)

if __name__ == "__main__":
    main()
