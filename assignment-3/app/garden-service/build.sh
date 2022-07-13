cp -R lib logic-component
cp -R lib mqtt-component

if [ $# -eq 0 ]
  then
    docker compose up -d --build
  else
    for service in "$@"
    do
        docker compose up -d --build --no-deps $service
    done
fi

rm -rf logic-component/lib/
rm -rf mqtt-component/lib/