if [ "$PS1" ]; then	 #01
  if [ -z "$PROMPT_COMMAND" ]; then #02
    case $TERM in #03
    xterm*|vte*)	#04
      if [ -e /etc/sysconfig/bash-prompt-xterm ]; then #05
          PROMPT_COMMAND=/etc/sysconfig/bash-prompt-xterm #06
      elif [ "${VTE_VERSION:-0}" -ge 3405 ]; then #07
          PROMPT_COMMAND="__vte_prompt_command" #08
      else
          PROMPT_COMMAND='printf "\033]0;%s@%s:%s\007" "${USER}" "${HOSTNAME%%.*}" "${PWD/#$HOME/~}"' #09
      fi
      ;;
    screen*) #10
      if [ -e /etc/sysconfig/bash-prompt-screen ]; then #11
          PROMPT_COMMAND=/etc/sysconfig/bash-prompt-screen #12
      else
          PROMPT_COMMAND='printf "\033k%s@%s:%s\033\\" "${USER}" "${HOSTNAME%%.*}" "${PWD/#$HOME/~}"'#13
      fi
      ;;
    *) #14
      [ -e /etc/sysconfig/bash-prompt-default ] && PROMPT_COMMAND=/etc/sysconfig/bash-prompt-default	 #15
      ;;
    esac
  fi
#01. ���� ���ִ� ������Ʈ�� Ŀ�ǵ�������Ʈ�̰�
#02. Ŀ�ǵ� ������Ʈ ��Ʈ���� ����ִٸ�
#03. TERM�̶�� ������
#04. xterm*, vte* ��� ������ ������ ���� ��
#05. /etc/sysconfig/�� bash-prompt-xterm ������ �����ϸ�
#06. �ش� bash-prompt-xterm ������ ����
#07. bash-prompt-xterm ������ ����, {VTE_VERSION:-0}�̶�� ������ 3405���� ũ�ų� ������
#08. __vte_prompt_command��� ��ɾ� ����
#09. �� �� ������ ��� �������� ������ ������ ���� Ŀ�ǵ� ����
#10. TERM�̶�� ������ screen* �̶�� ������ ������ ���� ��
#11. bash-prompt-screen ������ �����ϸ�
#12. �ش� bash-prompt-screen ���� ����
#13. ������ ���� Ŀ�ǵ� ����
#14. TERM�̶�� ������ �� ������ ��� �������� ���� ��
#15. bash-prompt-default ������ �����ϸ� �ش� ���� ����
  shopt ?s histappend #16
  history ?a #17
  shopt ?s checkwinsize #18
  [ "$PS1" = "\\s-\\v\\\$ " ] && PS1="[\u@\h \W]\\$ " #19
fi
#16. �� �ɼ� �� histappend ��� �ɼ� Ȱ��ȭ(set)
#17. ���ο� history ���ε��� �߰��Ѵ�.
#18. �� �ɼ� �� checkwinsize ��� �ɼ� Ȱ��ȭ(set)
#19. ���� PS1������ \\s-\\v\\\$�� PS1�� "[\u@\h \W]\\$ " ���ڿ��� ����
if ! shopt -q login_shell ; then #20
    # Need to redefine pathmunge, it get's undefined at the end of /etc/profile #21
    pathmunge () {	#22
        case ":${PATH}:" in	#23
            *:"$1":*)		#24
                ;;
            *)		#25
                if [ "$2" = "after" ] ; then	#26
                    PATH=$PATH:$1		#27
                else				#28
                    PATH=$1:$PATH		#29
                fi
        esac
    }

#20. �α��ν��� ����ǥ�ð� ������ ���°� �ƴϸ�
#21. /etc/profile ���� ���� ���ǰ� �Ǿ����� �ʾƼ� pathmunge�� �缳�� �ؾ��Ѵ�.
#22. ����� ���� �Լ��� ����
#23. $PATH ������
#24. ��$1���� �߰��� ��������� �ƹ��͵� ����
#25. �� ������ �ȸ°�
#26. ���� $2�� ���빰�� after��� ��Ʈ���̸�
#27. PATH ���� �ڿ� $1 �߰�
#28. after ��Ʈ���� �ƴϸ�
#29. PATH ���� �տ� $1 �߰�

    if [ $UID -gt 199 ] && [ "`id -gn`" = "`id -un`" ]; then	#30
       umask 002					#31
    else
       umask 022					#32
    fi

    SHELL=/bin/bash	#33

    for i in /etc/profile.d/*.sh; do	#34
        if [ -r "$i" ]; then		#35
            if [ "$PS1" ]; then		#36
                . "$i"		#37
            else
                . "$i" >/dev/null	#38
            fi
        fi
    done

    unset i			#39
    unset -f pathmunge		# 
fi

#30. UID������ 199���� ũ��, �׷��̸��� �����̸��� ���ٸ�
#31. umask�� 002��
#32. �ƴϸ� 022�� ����
#33. �⺻ ���� bash�� ����
#34. i�� /etc/profile.d/�� �����ϴ� .sh ���ϵ��� �̸���� �ٲ㰡�鼭 ����
#35. ���� i����(sh����)�� ���� �� �ְ�
#36. PS1 ������ ��(�����̸�)�� �����ϸ�
#37. �ش� ����(i.sh)�� ����
#38. PS1 ������ ���� ������ ��ŵ
#39. ���� i�� �Լ� pathmunge ���� ����