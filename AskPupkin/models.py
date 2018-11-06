from django.contrib.auth.models import User
from django.db import models

# TODO(): убрать сырые SQL
# Create your models here.
from django.db.models import Count
from django.db.models.expressions import RawSQL
from django.utils import timezone


class Profile(models.Model):
    user_img = models.ImageField(upload_to='static/usr_img', default='static/usr_img/default')
    user = models.OneToOneField(User, on_delete=models.CASCADE)


class TagManager(models.Manager):
    def with_question_count(self):
        return self.annotate(questions_count=Count('question'))

    def order_by_question_count(self):
        return self.with_question_count().order_by('-questions_count')

    def get_by_title(self, title):
        return self.get(title=title)


class Tag(models.Model):
    title = models.CharField(max_length=30)
    object = TagManager()


class QuestionQuerySet(models.QuerySet):
    def with_tags(self):
        return self.prefetch_related('tags')

    def with_answers_count(self):
        return self.annotate(answers=Count('answer__id', distinct=True))

    def with_author(self):
        return self.select_related('author').select_related('author__profile')

    def with_likes(self):
        return self.annotate(likes=RawSQL('''
            SELECT IFNULL(SUM(value), 0) 
            FROM {QuestionLike} AS quest_like 
            WHERE quest_like.question_id = {Question}.id '''.format(
            Question=Question._meta.db_table,
            QuestionLike=QuestionLike._meta.db_table), ()))

    def order_by_popularity(self):
        return self.order_by('-likes')


class QuestionManager(models.Manager):
    def get_queryset(self):
        res = QuestionQuerySet(self.model, using=self._db)
        return res.with_answers_count().with_likes().with_author().with_tags()

    def list_new(self):
        return self.order_by('-date')

    def list_hot(self):
        return self.get_queryset().order_by_popularity()

    def list_tag(self, tag):
        return self.filter(tags=tag)

    def get_single(self, _id):
        res = self.get_queryset()
        return res.get(pk=_id)


class Question(models.Model):
    title = models.CharField(max_length=100)
    text = models.TextField()
    author = models.ForeignKey(User, on_delete=models.CASCADE)
    date = models.DateTimeField(default=timezone.now)
    tags = models.ManyToManyField(Tag)
    object = QuestionManager()


class AnswerQuerySet(models.QuerySet):
    def with_author(self):
        return self.select_related('author').select_related('author__profile')

    def with_likes(self):
        return self.annotate(likes=RawSQL('''
            SELECT IFNULL(SUM(value), 0) 
            FROM {AnswerLike} AS answer_like 
            WHERE answer_like.answer_id = {Answer}.id '''.format(
            Answer=Answer._meta.db_table,
            AnswerLike=AnswerLike._meta.db_table), ()))

    def order_by_popularity(self):
        return self.order_by('-likes')


class AnswerManager(models.Manager):
    def get_queryset(self):
        res = AnswerQuerySet(self.model, using=self._db)
        return res.with_likes().order_by_popularity()

    def get_for_question(self, question):
        return self.filter(question=question)


class Answer(models.Model):
    text = models.TextField()
    question = models.ForeignKey(Question, on_delete=models.CASCADE)
    author = models.ForeignKey(User, on_delete=models.CASCADE)
    date = models.DateTimeField(default=timezone.now)
    is_correct = models.BooleanField(default=False)
    objects = AnswerManager()


class AnswerLike(models.Model):
    answer = models.ForeignKey(Answer, on_delete=models.CASCADE)
    user = models.ForeignKey(User, on_delete=models.CASCADE)
    value = models.SmallIntegerField(default=1)


class QuestionLike(models.Model):
    question = models.ForeignKey(Question, on_delete=models.CASCADE)
    user = models.ForeignKey(User, on_delete=models.CASCADE)
    value = models.SmallIntegerField(default=1)
