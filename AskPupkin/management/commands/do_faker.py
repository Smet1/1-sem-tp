from faker import Factory
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

    USERS_COUNT = 75
    QUESTIONS_COUNT = 150
    TAGS_COUNT = 5
    MIN_ANSWERS = 5
    MAX_ANSWERS = 15

    def add_arguments(self, parser):
        pass

    def create_users(self):
        for i in range(0, self.USERS_COUNT):
            profile = self.faker.simple_profile()

            usr = User()
            usr.username = profile['username']
            usr.first_name = self.faker.first_name()
            usr.last_name = self.faker.last_name()
            usr.email = profile['mail']
            usr.password = make_password('web')
            usr.is_active = True
            usr.is_superuser = False
            usr.save()

            up = Profile()
            up.user = usr

            image_url = 'https://robohash.org/%s.png' % usr.id
            content = request.urlretrieve(image_url)
            up.user_img.save('%s.png' % usr.username, File(open(content[0], 'rb')), save=True)
            up.save()

            self.stdout.write('[%d] added user %s' % (usr.id, usr.username))

    def create_questions(self):
        users = User.objects.all()[1:]

        for i in range(0, self.QUESTIONS_COUNT):
            quest = Question()

            quest.title = self.faker.sentence(nb_words=randint(4, 6), variable_nb_words=True)
            quest.text = self.faker.paragraph(nb_sentences=randint(4, 13), variable_nb_sentences=True),

            quest.author = choice(users)
            quest.save()

            self.stdout.write('[%d] added question' % quest.id)

    def create_answers(self):
        users = User.objects.all()[1:]
        questions = Question.object.all()

        for question in questions:
            for i in range(0, randint(self.MIN_ANSWERS, self.MAX_ANSWERS)):
                answer = Answer()
                answer.author = choice(users)
                answer.text = self.faker.paragraph(nb_sentences=randint(2, 10), variable_nb_sentences=True),
                answer.question = question
                answer.correct = True if i == 0 else False
                answer.save()

                self.stdout.write('[%d] added answer' % answer.id)

    def create_likes(self):
        users = User.objects.all()[1:]
        questions = Question.object.all()
        answers = Answer.object.all()

        for question in questions:
            for i in range(0, randint(0, self.USERS_COUNT // 10)):
                quest_like = QuestionLike()
                quest_like.user = users[i]
                quest_like.value = choice([-1, 1])
                quest_like.question = question
                quest_like.save()

                self.stdout.write('[%d] liked question' % question.id)

        for answer in answers:
            for i in range(0, randint(0, self.USERS_COUNT // 10)):
                answer_like = AnswerLike()
                answer_like.user = users[i]
                answer_like.value = choice([-1, 1])
                answer_like.answer = answer
                answer_like.save()

                self.stdout.write('[%d] liked answer' % answer.id)

    def create_tags(self):
        tags = [
            'JavaScript', 'Java', 'C#', 'Android', 'Ajax', 'Python', 'FireFox', 'Mail.ru', 'TechnoPark', 'Perl'
            'HTML', 'CSS', 'C++', 'iOS', 'MySQL', 'Objective-C', 'Django', 'ASM', 'SQL', '.net', 'RUBY', 'Swift'
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

            self.stdout.write('[%d] tagged question' % question.id)

    def handle(self, *args, **options):
        self.create_users()
        self.create_questions()
        self.create_answers()
        self.create_likes()
        self.create_tags()
