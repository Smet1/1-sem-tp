# -*- coding: utf-8 -*-
from faker import Factory
import codecs
from django.core.management.base import BaseCommand
from django.contrib.auth.hashers import make_password
from django.contrib.auth.models import User
from AskPupkin.models import Question, Answer, Tag, Profile, AnswerLike, QuestionLike
from random import choice, randint
import urllib.request as request
from django.core.files import File


class Command(BaseCommand):
    help = 'Fills database with fake data'
    faker = Factory.create()

    USERS_COUNT = 20
    QUESTIONS_COUNT = 50
    TAGS_COUNT = 3
    MIN_ANSWERS = 4
    MAX_ANSWERS = 13

    def add_arguments(self, parser):
        pass

    def create_users(self):

        for i in range(0, self.USERS_COUNT):
            profile = self.faker.simple_profile()

            u = User()
            u.username = profile['username']
            u.first_name = self.faker.first_name()
            u.last_name = self.faker.last_name()
            u.email = profile['mail']
            u.password = make_password('web')
            u.is_active = True
            u.is_superuser = False
            u.save()

            up = Profile()
            up.user = u

            image_url = 'https://robohash.org/%s.png' \
                        % u.id
            content = request.urlretrieve(image_url)
            up.user_img.save('%s.png' % u.username, File(open(content[0], 'rb')), save=True)
            up.save()

            self.stdout.write('[%d] added user %s' % (u.id, u.username))

    def create_questions(self):
        users = User.objects.all()[1:]

        for i in range(0, self.QUESTIONS_COUNT):
            q = Question()

            q.title = self.faker.sentence(nb_words=randint(4, 6), variable_nb_words=True)
            q.text = self.faker.paragraph(nb_sentences=randint(4, 13), variable_nb_sentences=True),

            q.author = choice(users)
            q.save()
            self.stdout.write('added question [%d]' % q.id)

    def create_answers(self):
        users = User.objects.all()[1:]
        questions = Question.object.all()

        for question in questions:
            for i in range(0, randint(self.MIN_ANSWERS, self.MAX_ANSWERS)):
                a = Answer()
                a.author = choice(users)
                a.text = self.faker.paragraph(nb_sentences=randint(2, 10), variable_nb_sentences=True),
                a.question = question
                a.correct = True if i == 0 else False
                a.save()
                self.stdout.write('added answer [%d]' % a.id)

    def create_likes(self):
        users = User.objects.all()[1:]
        questions = Question.object.all()
        answers = Answer.object.all()

        for question in questions:
            for i in range(0, randint(0, self.USERS_COUNT // 10)):
                like = QuestionLike()
                like.user = users[i]
                like.value = choice([-1, 1])
                like.question = question
                self.stdout.write('liked question [%d]' % question.id)
                like.save()

        for answer in answers:
            for i in range(0, randint(0, self.USERS_COUNT // 10)):
                like = AnswerLike()
                like.user = users[i]
                like.value = choice([-1, 1])
                like.answer = answer
                self.stdout.write('liked answer [%d]' % answer.id)
                like.save()

    def create_tags(self):
        tags = [
            'JavaScript', 'Java', 'C#', 'Android', 'Ajax', 'Python', 'FireFox', 'Mail.ru', 'TechnoPark', 'Perl'
            'HTML', 'CSS', 'C++', 'iOS', 'MySQL', 'Objective-C', 'Django', 'ASM',
            'SQL', '.net', 'RUBY', 'Swift'
        ]
        for tag in tags:
            if len(Tag.object.filter(title=tag)) == 0:
                t = Tag()
                t.title = tag
                t.save()

        tags = Tag.object.all()
        questions = Question.object.all()
        for question in questions:
            for i in range(0, self.TAGS_COUNT):
                t = choice(tags)

                if t not in question.tags.all():
                    question.tags.add(t)
            self.stdout.write('tagged question [%d]' % question.id)

    def handle(self, *args, **options):
        self.create_users()
        self.create_questions()
        self.create_answers()
        self.create_likes()
        self.create_tags()
