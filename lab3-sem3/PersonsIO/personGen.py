from faker import Faker
import random

fake = Faker()

# Function to generate random gender
def generate_gender():
    return random.choice(['Male', 'Female'])

# Function to generate name based on gender
def generate_name(gender):
    if gender == 'Male':
        return fake.first_name_male()
    else:
        return fake.first_name_female()

# Function to generate height based on gender
def generate_height(gender):
    if gender == 'Male':
        return round(random.uniform(160, 190), 2)  # Height in cm for males
    else:
        return round(random.uniform(150, 180), 2)  # Height in cm for females

# Function to generate weight based on gender
def generate_weight(gender):
    if gender == 'Male':
        return round(random.uniform(60, 100), 2)  # Weight in kg for males
    else:
        return round(random.uniform(50, 80), 2)  # Weight in kg for females

# Function to generate hobby based on gender
def generate_hobby(gender):
    if (random.random() > 0.7):
        if gender == 'Male':
            return fake.random_element(elements=('Sports', 'Gaming', 'Fishing', 'Hiking', 'Chess', 'Cooking'))
        else:
            return fake.random_element(elements=('Reading', 'Yoga', 'Painting', 'Dancing', 'Cooking', 'Traveling'))
    else:
        if gender == 'Female':
            return fake.random_element(elements=('Sports', 'Gaming', 'Fishing', 'Hiking', 'Chess', 'Cooking'))
        else:
            return fake.random_element(elements=('Reading', 'Yoga', 'Painting', 'Dancing', 'Cooking', 'Traveling'))
# Generate 100 persons with their characteristics
persons = []
for _ in range(100):
    gender = generate_gender()
    person = {
        'name': generate_name(gender),
        'surname': fake.last_name(),
        'height': generate_height(gender),
        'weight': generate_weight(gender),
        'country': fake.country(),
        'city': fake.city(),
        'region': fake.state(),
        'gender': gender,
        'hobby': generate_hobby(gender)
    }
    persons.append(person)

# Write the list of persons to a text file
with open('person_list_gender_dependent.txt', 'w') as f:
    for person in persons:
        f.write(f"Name: {person['name']}\n")
        f.write(f"Surname: {person['surname']}\n")
        f.write(f"Height: {person['height']} cm\n")
        f.write(f"Weight: {person['weight']} kg\n")
        f.write(f"Country: {person['country']}\n")
        f.write(f"City: {person['city']}\n")
        f.write(f"Region: {person['region']}\n")
        f.write(f"Gender: {person['gender']}\n")
        f.write(f"Hobby: {person['hobby']}\n")
        f.write('\n')
