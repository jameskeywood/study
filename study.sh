if [ $1 == "start" ]
then
	s_date=$(date "+%d%m%y")
	s_start=$(date "+%s")

	echo "$s_date"

	trap 's_end=$(date "+%s");
	  	  s_secs=$(bc <<< "$s_end - $s_start");
		  s_mins=$(bc <<< "$s_secs / 60");

		  # combine minutes if date the same
		  prev_date=$(tail -n 1 times.csv | cut -d, -f1)
		  if [ $s_date == $prev_date ]
		  then
			  prev_mins=$(tail -n 1 times.csv | cut -d, -f2)
			  s_mins=$(bc <<< "$s_mins + $prev_mins")

			  # delete last line
			  sed -i "$ d" times.csv
		  fi


		  echo "$s_date,$s_mins" >> times.csv;
          echo "Saved: $s_date,$s_mins";
		  exit' SIGINT

	sox -n -d synth -1 brownnoise vol 0.01 &> /dev/null
elif [ $1 == "view" ]
then
	gnuplot -e 'set datafile separator ",";
				set title "Focused study minutes per day";
				set terminal dumb enhanced ansi fillchar "-";
				set style data histograms;
				set style fill solid;
				set yrange [0:*];
				plot "times.csv" using 2:xtic(1) notitle;'
fi
