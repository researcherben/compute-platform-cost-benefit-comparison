# https://hub.docker.com/_/centos?tab=tags
FROM centos:7

MAINTAINER ben

LABEL remarks="an example"

RUN yum -y install centos-release-scl

RUN yum -y groupinstall 'Development Tools'

RUN yum -y install epel-release octave octave-devel 


