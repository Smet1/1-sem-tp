from django.http import HttpResponse, Http404
from django.contrib.auth import authenticate
from django.contrib.auth.models import User
from django.contrib.auth.hashers import make_password
from django.core.files import File
from django import forms

from AskPupkin.models import Profile


class LoginForm(forms.Form):
    login = forms.CharField(
        label='Login',
        widget=forms.TextInput(attrs={'class': 'form-control', 'placeholder': 'Enter your Username here'}),
        max_length=30
    )

    password = forms.CharField(
        label='Password',
        widget=forms.PasswordInput(attrs={'class': 'form-control', 'placeholder': '*******'}),
        min_length=8
    )

    def clean(self):
        data = self.cleaned_data
        user_username = data.get('login', '')
        user_password = data.get('password', '')

        user = authenticate(username=user_username, password=user_password)

        if user is not None:
            if user.is_active:
                data['user'] = user
            else:
                raise forms.ValidationError('User is not active')
        else:
            raise forms.ValidationError('Wrong login or password')


class SignupForm(forms.Form):
    username = forms.CharField(
        label='Login',
        widget=forms.TextInput(attrs={'class': 'form-control', 'placeholder': 'dr_pepper'}),
        max_length=30
    )

    email = forms.EmailField(
        label='Email',
        widget=forms.EmailInput(attrs={'class': 'form-control', 'placeholder': 'dr.pepper@mail.ru'}),
        max_length=100
    )

    nick_name = forms.CharField(
        label='NickName',
        widget=forms.TextInput(attrs={'class': 'form-control', 'placeholder': 'Dr. Pepper'}),
        max_length=30
    )

    password = forms.CharField(
        label='Password',
        widget=forms.PasswordInput(attrs={'class': 'form-control', 'placeholder': '*******'}),
        min_length=8
    )

    password_repeat = forms.CharField(
        label='Repeat Password',
        widget=forms.PasswordInput(attrs={'class': 'form-control', 'placeholder': '*******'}),
        min_length=8
    )

    avatar = forms.FileField(
        label='Upload avatar',
        widget=forms.ClearableFileInput(attrs={}),
        required=False
    )

    def clean_username(self):
        username = self.cleaned_data.get('username', '')

        try:
            User.objects.get(username=username)

            raise forms.ValidationError('Username is already used')
        except User.DoesNotExist:

            return username

    def clean_nick_name(self):
        nickname = self.cleaned_data.get('nick_name', '')

        try:
            User.objects.get(last_name=nickname)

            raise forms.ValidationError('NickName is already used')
        except User.DoesNotExist:

            return nickname

    def clean_password_repeat(self):
        password = self.cleaned_data.get('password', '')
        password_repeat = self.cleaned_data.get('password_repeat', '')

        if password != password_repeat:
            raise forms.ValidationError('Passwords does not matched')

        return password_repeat

    def clean_email(self):
        email = self.cleaned_data.get('email', '')

        try:
            User.objects.get(email=email)

            raise forms.ValidationError('Email is already used')
        except User.DoesNotExist:
            return email

    def clean_avatar(self):
        avatar = self.cleaned_data.get('avatar')

        return avatar

    def save(self):
        data = self.cleaned_data
        password = data.get('password')
        u = User()

        u.username = data.get('username')
        u.last_name = data.get('nick_name')
        u.password = make_password(password)
        u.email = data.get('email')
        u.is_active = True
        u.is_superuser = False
        u.save()

        up = Profile()
        up.user = u
        up.rating = 0

        if data.get('avatar') is not None:
            avatar = data.get('avatar')
            up.user_img.save('%s.png' % u.username, avatar, save=True)

        up.save()

        return authenticate(username=u.username, password=password)
