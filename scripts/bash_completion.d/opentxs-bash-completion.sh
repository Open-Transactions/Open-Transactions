# opentxs bash-completion (Open Transactions Project - opentransactions.org)
# autocompletion for opentxs commands (Open Transactions command-line client)

_opentxs_complete()
{
    local cur_word prev_word type_list

    # COMP_WORDS is an array of words in the current command line.
    # COMP_CWORD is the index of the current word (the one the cursor is
    # in). So COMP_WORDS[COMP_CWORD] is the current word; we also record
    # the previous word here, although this specific script doesn't
    # use it yet.
    cur_word="${COMP_WORDS[COMP_CWORD]}"
    prev_word="${COMP_WORDS[COMP_CWORD-1]}"

    # Ask opentxs to generate a list of types it supports
    type_list='acceptall acceptinbox acceptinvoices acceptmoney acceptpayments acceptreceipts accepttransfers addasset addserver addsignature balance buyvoucher cancel changepw checknym clearexpired clearrecords 
confirm credentials decode decrypt delmail deloutmail deposit discard editacct editasset editnym editserver encode encrypt exchange expired exportcash exportnym getboxreceipt getcontract getmarkets getmyoffers 
getoffers importcash importnym inbox issueasset killoffer killplan mail newacct newasset newbasket newcred newkey newnym newoffer newserver outbox outmail outpayment pass_decrypt pass_encrypt paydividend payinvoice 
payments propose records refresh refreshacct refreshnym register revokecred sendcash sendcheque sendinvoice sendmsg sendvoucher showaccounts showacct showassets showbasket showcred showincoming showmarkets showmint 
showmyoffers shownym shownyms showoffers showoutgoing showpayment showpurse showservers sign stat transfer trigger verifyreceipt verifysig withdraw writecheque writeinvoice'

    # COMPREPLY is the array of possible completions, generated with
    # the compgen builtin.
    if [[ ${prev_word} == 'opentxs' ]] ; then
    	COMPREPLY=( $(compgen -W "${type_list}" -- ${cur_word}) )
    else
        COMPREPLY=()
    fi
    return 0
}

# Register _pss_complete to provide completion for the following commands
complete -F _opentxs_complete opentxs
