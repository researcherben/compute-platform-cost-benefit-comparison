# https://hub.docker.com/_/centos?tab=tags
FROM centos:7

MAINTAINER ben

LABEL remarks="an example"

RUN yum -y install python3

RUN yum -y install centos-release-scl

RUN yum -y install python3-pip

RUN yum -y groupinstall 'Development Tools'

COPY requirements.txt requirements.txt
RUN pip3 install -r requirements.txt

