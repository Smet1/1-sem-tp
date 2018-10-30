from django.shortcuts import render


# Create your views here.

def home_page(request):
    return render(request, 'index.html')


def question_page(request):
    return render(request, 'question.html')


def ask_page(request):
    return render(request, 'ask.html')


def signup_page(request):
    return render(request, 'signup.html')

