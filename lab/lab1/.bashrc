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
#01. 현재 떠있는 프롬프트가 커맨드프롬프트이고
#02. 커맨드 프롬프트 스트링이 비어있다면
#03. TERM이라는 변수가
#04. xterm*, vte* 라는 변수를 가지고 있을 때
#05. /etc/sysconfig/에 bash-prompt-xterm 파일이 존재하면
#06. 해당 bash-prompt-xterm 파일을 실행
#07. bash-prompt-xterm 파일이 없고, {VTE_VERSION:-0}이라는 변수가 3405보다 크거나 같으면
#08. __vte_prompt_command라는 명령어 실행
#09. 위 두 조건을 모두 만족하지 않으면 다음과 같은 커맨드 실행
#10. TERM이라는 변수가 screen* 이라는 패턴을 가지고 있을 때
#11. bash-prompt-screen 파일이 존재하면
#12. 해당 bash-prompt-screen 파일 실행
#13. 없으면 다음 커맨드 실행
#14. TERM이라는 변수가 위 패턴을 모두 만족하지 않을 때
#15. bash-prompt-default 파일이 존재하면 해당 파일 실행
  shopt ?s histappend #16
  history ?a #17
  shopt ?s checkwinsize #18
  [ "$PS1" = "\\s-\\v\\\$ " ] && PS1="[\u@\h \W]\\$ " #19
fi
#16. 쉘 옵션 중 histappend 라는 옵션 활성화(set)
#17. 새로운 history 라인들을 추가한다.
#18. 쉘 옵션 중 checkwinsize 라는 옵션 활성화(set)
#19. 현재 PS1내용이 \\s-\\v\\\$면 PS1에 "[\u@\h \W]\\$ " 문자열을 넣음
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

#20. 로그인쉘이 정상표시가 가능한 상태가 아니면
#21. /etc/profile 파일 끝에 정의가 되어있지 않아서 pathmunge를 재설정 해야한다.
#22. 사용자 정의 함수를 생성
#23. $PATH 변수에
#24. “$1”가 중간에 들어있으면 아무것도 안함
#25. 위 조건이 안맞고
#26. 변수 $2의 내용물이 after라는 스트링이면
#27. PATH 변수 뒤에 $1 추가
#28. after 스트링이 아니면
#29. PATH 변수 앞에 $1 추가

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

#30. UID변수가 199보다 크고, 그룹이름과 유저이름이 같다면
#31. umask를 002로
#32. 아니면 022로 지정
#33. 기본 쉘을 bash로 지정
#34. i를 /etc/profile.d/에 존재하는 .sh 파일들의 이름들로 바꿔가면서 실행
#35. 만약 i변수(sh파일)를 읽을 수 있고
#36. PS1 변수에 값(파일이름)이 존재하면
#37. 해당 파일(i.sh)을 실행
#38. PS1 변수에 값이 없으면 스킵
#39. 변수 i와 함수 pathmunge 선언 해제