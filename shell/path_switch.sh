#! /bin/bash
# longbin
# 2017-04-01
# dtags.sh

# dtag   [tag_name]
# duntag <tag_name>
# djump  <tag_name>

export __DIR_TAGS_PATH=${HOME}/.dtags

function print_length_str()
{
	local target_length=${COLUMN1_WIDTH_MAX:=8}
	local str_length=$(echo $*|wc -c)

	echo -n "$*"
	for (( ;str_length<=target_length;str_length++ ))
	do
		# 如果字符长度不够就用空格补齐
		echo -n ' '
	done
}

function show_dtags_func()
{
	local COLUMN_SEP='----> '
	COLUMN1_WIDTH_MAX=8

	# 获取COLUMN1_WIDTH_MAX
	DIR_TAGS_LIST=$(ls ${__DIR_TAGS_PATH})
	for line in ${DIR_TAGS_LIST}
	do
		if [[ "$(echo ${line}|wc -c)" -gt "${COLUMN1_WIDTH_MAX}" ]] ;then
			let COLUMN1_WIDTH_MAX=$(echo ${line}|wc -c)
		fi
	done

	# 显示每条dtag的具体信息
	DIR_TAGS_DETAILS=$(ls -l ${__DIR_TAGS_PATH}|awk '{print $9"->"$11}')
	for line in ${DIR_TAGS_DETAILS}
	do
		line_col1=$(echo ${line}|awk -F'->' '{print $1}')
		line_col2=$(echo ${line}|awk -F'->' '{print $2}')
		if [[ "${line_col1}" == "" ]] ;then
			continue
		fi
		print_length_str "${line_col1}"
		echo "${COLUMN_SEP}${line_col2}"
	done
}

function dtag()
{
	if [[ "$*" == "--help" ]] ;then
		echo -e "Usage:\n\tdtag    [tag_name]"
		return 0
	fi
	local dtag=$1

	[[ -d ${__DIR_TAGS_PATH} ]] || mkdir -p ${__DIR_TAGS_PATH}
	if [[ "$?" != "0" ]] ;then
		echo "ERROR: permission denied."
		return 1
	fi

	# 如果参数为空则显示所有已创建的dtags
	# 如果只有一个参数则创建相应的dtag
	# 否则报错
	if [[ "$#" == "0" ]] ;then
		# show all created dtags
		if [[ "$(ls ${__DIR_TAGS_PATH})" == "" ]] ;then
			echo -e "Usage:\n\tdtag    <tag_name>"
		else
			# 显示所有已创建dtags的具体信息
			show_dtags_func
		fi
		return 0
	elif [[ "$#" == "1" ]] ;then
		# create dtag
		rm -f ${__DIR_TAGS_PATH}/${dtag}
		ln -s $(pwd) ${__DIR_TAGS_PATH}/${dtag} 2>/dev/null
		if [[ "$?" != "0" ]] ;then
			echo "ERROR: permission denied."
			return 1
		fi
		return 0
	else
		echo -e "Usage:\n\tdtag    [tag_name]"
		return 1
	fi
}

function duntag()
{
	if [[ "$*" == "--help" ]] ;then
		echo -e "Usage:\n\tduntag  <tag_name>"
		return 0
	fi
	local dtag=$1
	[[ -d ${__DIR_TAGS_PATH} ]] || mkdir -p ${__DIR_TAGS_PATH}
	if [[ "$?" != "0" ]] ;then
		echo "ERROR: permission denied."
		return 1
	fi
	
	# 如果不知一个参数则显示已创建的dtags和帮助信息
	# 如果只有一个参数则删除相应的dtag
	if [[ "$#" -ne "1" ]] ;then
		# show all created dtags
		echo -e "Usage:\n\tduntag  <tag_name>"
		if [[ "$(ls ${__DIR_TAGS_PATH})" != "" ]] ;then
			echo -e "\nThe tag_name could be:"
			for line in $(ls ${__DIR_TAGS_PATH})
			do
				echo -e "\t${line}"
			done
		fi
		return 1
	fi
	if [[ -e ${__DIR_TAGS_PATH}/${dtag} ]] ;then
		read -p "remove dtag: \`${dtag}'? " user_select
		if [[ "${user_select/Y/y}" == "y" ]] ;then
			rm -f ${__DIR_TAGS_PATH}/${dtag} 2>/dev/null
			if [[ "$?" != "0" ]] ;then
				echo "ERROR: permission denied."
				return 1
			fi
		fi
	else
		echo "ERROR: ${dtag}: No such dtag."
		return 1
	fi
}

function djump()
{
	if [[ "$*" == "--help" ]] ;then
		echo -e "Usage:\n\tduntag  <tag_name>"
		return 0
	fi
	local dtag=$1
	[[ -d ${__DIR_TAGS_PATH} ]] || mkdir -p ${__DIR_TAGS_PATH}
	if [[ "$?" != "0" ]] ;then
		echo "ERROR: permission denied."
		return 1
	fi
	
	# 如果只有一个参数则直接跳转
	# 否则给出帮助信息和可以选择的参数
	if [[ "$#" -ne "1" ]] ;then
		# show all created dtags
		echo -e "Usage:\n\tdjump   <tag_name>"
		if [[ "$(ls ${__DIR_TAGS_PATH})" != "" ]] ;then
			echo -e "\nThe tag_name could be:"
			for line in $(ls ${__DIR_TAGS_PATH})
			do
				echo -e "\t${line}"
			done
		fi
		return 1
	fi
	if [[ -e ${__DIR_TAGS_PATH}/${dtag} ]] ;then
		cd -P ${__DIR_TAGS_PATH}/${dtag} 2>/dev/null || echo "ERROR: ${dtag}: No such dtag."
	else
		echo "ERROR: ${dtag}: No such dtag."
		return 1
	fi
}

# 为duntag和djump命令提供TAB键自动补全功能
function __complete_dtags()
{
	local curw=${COMP_WORDS[COMP_CWORD]}
	local wordlist=$(find ${__DIR_TAGS_PATH} -type l -printf "%f\n" )
	# 定义双击TAB后显示的结果;compgen -W基于curw提供可能的补全
	COMPREPLY=( $(compgen -W '${wordlist[@]}' -- "${curw}" ) )
}
complete -F __complete_dtags duntag djump

