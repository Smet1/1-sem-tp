from django.shortcuts import render


# Create your views here.

def home_page(request):
    return render(request, 'index.html')


def question_id(request):
    return render(request, 'question.html')
