from django.shortcuts import render
from faker import Faker

fake = Faker('ru_RU')


# Create your views here.

def home_page(request):
    return render(request, 'index.html')


def question_page(request, question_id):
    quest = {
        'id': 0,
        'title': fake.sentence(),
        'text': fake.text()
    }

    tags = [
        {
            'tag': fake.sentence(nb_words=1)
        } for x in range(3)
    ]

    responses = [
        {
            'id': id_res,
            'text': fake.text()
        } for id_res in range(5)
    ]
    return render(request, 'question.html', {'questions': quest, 'tags': tags, 'responses': responses})


def ask_page(request):
    return render(request, 'ask.html')


def signup_page(request):
    return render(request, 'signup.html')


def login_page(request):
    return render(request, 'login.html')


def tag_page(request, tag_sort):
    quest = [
        {
            'id': quest_id,
            'title': fake.sentence(),
            'text': fake.text(),
            'tags': [
                {
                    'tag': fake.sentence(nb_words=1)
                } for x in range(3)
            ],
        } for quest_id in range(6)
    ]

    for x in quest:
        x['tags'].append({'tag': tag_sort})

    return render(request, 'index_by_tag.html', {'questions': quest, 'tag_sort': tag_sort})

