from django.shortcuts import render, get_object_or_404
from faker import Faker
from AskPupkin.funcs import paginate
import random

from AskPupkin.models import Question, Answer, Tag

fake = Faker()


# Create your views here.

def home_page(request):
    # quest = [
    #     {
    #         'id': quest_id,
    #         'title': fake.sentence(),
    #         'text': fake.text(),
    #         'raiting': random.randint(0, 2000),
    #         'tags': [
    #             {
    #                 'tag': fake.sentence(nb_words=1)
    #             } for x in range(3)
    #         ],
    #     } for quest_id in range(40)
    # ]
    quest = Question.object.list_new()
    quest = paginate(request, quest)
    return render(request, 'index.html', {'questions': quest, 'title': 'new'})


def question_page(request, question_id):
    # quest = {
    #     'id': 0,
    #     'title': fake.sentence(),
    #     'text': fake.text(),
    #     'raiting': random.randint(0, 2000),
    # }
    #
    # tags = [
    #     {
    #         'tag': fake.sentence(nb_words=1)
    #     } for x in range(3)
    # ]
    #
    # responses = [
    #     {
    #         'id': id_res,
    #         'text': fake.text()
    #     } for id_res in range(15)
    # ]
    quest = Question.object.get_single(question_id)
    responses = Answer.object.get_for_question(quest)
    responses = paginate(request, responses, 10)

    return render(request, 'question.html', {'questions': quest, 'responses': responses})


def ask_page(request):
    return render(request, 'ask.html')


def signup_page(request):
    return render(request, 'signup.html')


def login_page(request):
    return render(request, 'login.html')


def tag_page(request, tag_sort):
    # quest = [
    #     {
    #         'id': quest_id,
    #         'title': fake.sentence(),
    #         'text': fake.text(),
    #         'raiting': random.randint(0, 2000),
    #         'tags': [
    #             {
    #                 'tag': fake.sentence(nb_words=1)
    #             } for x in range(3)
    #         ],
    #     } for quest_id in range(20)
    # ]
    #
    # for x in quest:
    #     x['tags'].append({'tag': tag_sort})
    tag = get_object_or_404(Tag, title=tag_sort)
    quest = Question.object.list_tag(tag)
    quest = paginate(request, quest)

    return render(request, 'index.html', {'questions': quest, 'title': 'tag', 'tag_sort': tag_sort})


def hot_page(request):
    # quest = [
    #     {
    #         'id': quest_id,
    #         'title': fake.sentence(),
    #         'text': fake.text(),
    #         'raiting': random.randint(0, 2000),
    #         'tags': [
    #             {
    #                 'tag': fake.sentence(nb_words=1)
    #             } for x in range(3)
    #         ],
    #     } for quest_id in range(30)
    # ]

    quest = Question.object.list_hot()
    quest = paginate(request, quest)

    return render(request, 'index.html', {'questions': quest, 'title': 'hot'})


def user_settings(request):
    return render(request, 'usr_settings.html')
