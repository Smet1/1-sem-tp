from django.contrib.auth.decorators import login_required
from django.http import HttpResponseRedirect
from django.shortcuts import render, get_object_or_404
from django.contrib import auth
from faker import Faker
from AskPupkin.funcs import paginate
from AskPupkin.forms import *

from AskPupkin.models import Question, Answer, Tag

fake = Faker()


# Create your views here.

def home_page(request):
    # print(request.user.profile.user_img.url)
    quest = Question.object.list_new()
    quest = paginate(request, quest)
    return render(request, 'index.html', {'questions': quest, 'title': 'new'})


def question_page(request, question_id):
    quest = Question.object.get_single(question_id)
    responses = Answer.objects.get_for_question(quest)
    responses = paginate(request, responses, 10)

    return render(request, 'question.html', {'questions': quest, 'responses': responses})


@login_required
def ask_page(request):
    return render(request, 'ask.html')


def signup_page(request):
    return render(request, 'signup.html')


def signup(request):
    if request.user.is_authenticated:
        return HttpResponseRedirect('/')
    if request.method == "POST":
        form = SignupForm(request.POST, request.FILES)
        if form.is_valid():
            user = form.save()
            auth.login(request, user)
            return HttpResponseRedirect('/')
    else:
        form = SignupForm()
    return render(request, 'signup.html', {'form': form})


def login_page(request):
    return render(request, 'login.html')


def login(request):
    redirect = request.GET.get('continue', '/')
    if request.user.is_authenticated:
        return HttpResponseRedirect(redirect)
    if request.method == "POST":
        form = LoginForm(request.POST)
        if form.is_valid():
            auth.login(request, form.cleaned_data['user'])
            return HttpResponseRedirect(redirect)
    else:
        form = LoginForm()
    return render(request, 'login.html', {'form': form})


@login_required
def logout(request):
    redirect = request.GET.get('continue', '/')
    auth.logout(request)
    return HttpResponseRedirect(redirect)


def tag_page(request, tag_sort):
    tag = get_object_or_404(Tag, title=tag_sort)
    quest = Question.object.list_tag(tag)
    quest = paginate(request, quest)

    return render(request, 'index.html', {'questions': quest, 'title': 'tag', 'tag_sort': tag_sort})


def hot_page(request):
    quest = Question.object.list_hot()
    quest = paginate(request, quest)

    return render(request, 'index.html', {'questions': quest, 'title': 'hot'})


@login_required
def user_settings(request):
    return render(request, 'usr_settings.html')
